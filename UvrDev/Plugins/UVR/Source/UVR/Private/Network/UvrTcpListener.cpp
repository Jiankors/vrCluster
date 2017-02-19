// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrTcpListener.h"



UvrTcpListener::UvrTcpListener(const FString& name) :
	m_name(name)
{
}


UvrTcpListener::~UvrTcpListener()
{
	// Just free resources by stopping the listening
	StopListening();
}


bool UvrTcpListener::StartListening(const FString& addr, const int32 port)
{
	FScopeLock lock(&m_cs);

	if (m_bIsListening == true)
		return true;

	FIPv4Endpoint ep;
	if (!UvrHelpers::net::GenIPv4Endpoint(addr, port, ep))
		return false;

	return StartListening(ep);
}

bool UvrTcpListener::StartListening(const FIPv4Endpoint& ep)
{
	FScopeLock lock(&m_cs);

	if (m_bIsListening == true)
		return true;

	// Save new endpoint
	m_Endpoint = ep;

	// Create listening thread
	m_pThread = FRunnableThread::Create(this, *(m_name + FString("_thread")), 1 * 1024, TPri_Normal);
	ensure(m_pThread);

	// Update state
	m_bIsListening = true;
	
	return m_bIsListening;
}


void UvrTcpListener::StopListening()
{
	FScopeLock lock(&m_cs);

	if (m_bIsListening == false)
		return;

	// Ask runnable to stop
	Stop();

	// Wait for thread finish and release it then
	if (m_pThread)
	{
		m_pThread->WaitForCompletion();
		delete m_pThread;
		m_pThread = nullptr;
	}
}

bool UvrTcpListener::IsActive() const
{
	return m_bIsListening;
}

bool UvrTcpListener::Init()
{
	// Create socket
	m_pSock = FTcpSocketBuilder(*m_name).AsBlocking().BoundToEndpoint(m_Endpoint).Listening(128);
	if (!m_pSock)
	{
		// Just exit. No need to perform some notification from this thread to the cluster manager to notify
		// about this fail. Just kill the application. 
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::KillImmediately, FString("Couldn't start listener socket"));
		return false;
	}

	return true;
}

uint32 UvrTcpListener::Run()
{
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	if (m_pSock)
	{
		while (FSocket* pSock = m_pSock->Accept(*RemoteAddress, TEXT("UvrTcpListener client")))
		{
			if (m_OnConnectionAccepted.IsBound())
			{
				if (!m_OnConnectionAccepted.Execute(pSock, FIPv4Endpoint(RemoteAddress)))
				{
					pSock->Close();
					ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(pSock);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogUvrNetwork, Error, TEXT("Socket is not initialized"));
		return 0;
	}

	return 0;
}

void UvrTcpListener::Stop()
{
	// Close the socket to unblock thread
	if(m_pSock)
		m_pSock->Close();
}

void UvrTcpListener::Exit()
{
	// Release the socket
	if (m_pSock)
	{
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_pSock);
		m_pSock = nullptr;
	}
}
