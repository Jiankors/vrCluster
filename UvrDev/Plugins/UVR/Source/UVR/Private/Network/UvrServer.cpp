// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrServer.h"



UvrServer::UvrServer(const FString& name, const FString& addr, const int32 port) :
	m_name(name),
	m_addr(addr),
	m_port(port),
	m_listener(name + FString("_listener"))
{
	check(port > 0 && port < 0xffff);
	
	// Bind connection handler method
	m_listener.OnConnectionAccepted().BindRaw(this, &UvrServer::ConnectionHandler);
}

UvrServer::~UvrServer()
{
	// Call from child .dtor
	Shutdown();
}

bool UvrServer::Start()
{
	FScopeLock lock(&m_cs);

	if (m_isRunning == true)
		return true;

	if (!m_listener.StartListening(m_addr, m_port))
	{
		UE_LOG(LogUvrNetwork, Error, TEXT("%s couldn't start the listener [%s:%d]"), *m_name, *m_addr, m_port);
		return false;
	}

	// Update server state
	m_isRunning = true;

	return m_isRunning;
}

void UvrServer::Shutdown()
{
	FScopeLock lock(&m_cs);

	if (m_isRunning == false)
		return;

	UE_LOG(LogUvrNetwork, Log, TEXT("%s stopping the service..."), *m_name);

	// Stop connections listening
	m_listener.StopListening();
	// Destroy active sessions
	m_sessions.Reset();
	// Update server state
	m_isRunning = false;
}

bool UvrServer::IsRunning()
{
	FScopeLock lock(&m_cs);
	return m_isRunning;
}

bool UvrServer::ConnectionHandler(FSocket* pSock, const FIPv4Endpoint& ep)
{
	FScopeLock lock(&m_cs);
	check(pSock);

	if (IsRunning() && IsConnectionAllowed(pSock, ep))
	{
		pSock->SetLinger(false, 0);
		pSock->SetNonBlocking(false);

		int32 newSize = static_cast<int32>(UvrConstants::net::SocketBufferSize);
		int32 setSize;
		pSock->SetReceiveBufferSize(newSize, setSize);
		pSock->SetSendBufferSize(newSize, setSize);

		m_sessions.Add(TUniquePtr<UvrSession>(new UvrSession(pSock, this, GetName() + FString("_session_") + ep.ToString())));
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrSessionListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrServer::NotifySessionOpen(UvrSession* pSession)
{
}

void UvrServer::NotifySessionClose(UvrSession* pSession)
{
	// Remove all other sessions except of this one because of deadlock
	//m_sessions.RemoveAll([pSession](const TUniquePtr<UvrSession>& item)
	//{
	//	return item.Get() != pSession;
	//});
}


