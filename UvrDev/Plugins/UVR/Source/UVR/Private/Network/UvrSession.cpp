// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSession.h"
#include "UvrServer.h"
#include "UvrMessage.h"


UvrSession::UvrSession(FSocket* pSock, IUvrSessionListener* pListener, const FString& name) :
	UvrSocketOps(pSock),
	m_pListener(pListener),
	m_name(name)
{
	check(pSock);
	check(pListener);

	m_pThread = FRunnableThread::Create(this, *(m_name + FString("_thread")), 128 * 1024, TPri_Normal, FPlatformAffinity::GetPoolThreadMask());
	ensure(m_pThread);

	m_pListener->NotifySessionOpen(this);

	UE_LOG(LogUvrNetwork, Log, TEXT("Session %s started"), *m_name);
}

UvrSession::~UvrSession()
{
	UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("Session %s .dtor"), *m_name);

	Stop();
	m_pThread->WaitForCompletion();
	delete m_pThread;
}

void UvrSession::Stop()
{
	GetSocket()->Close();
}

uint32 UvrSession::Run()
{
	UE_LOG(LogUvrNetwork, Log, TEXT("Session thread %s started"), *m_name);

	while (IsOpen())
	{
		auto req = RecvMsg();
		if (req.IsValid())
		{
			auto resp = m_pListener->ProcessMessage(req);
			if (resp.IsValid())
			{
				if (SendMsg(resp))
				{
					// 'Transaction' has been completed successfully so we continue the processing
					continue;
				}
			}
		}

		GetSocket()->Close();
		m_pListener->NotifySessionClose(this);
	}

	UE_LOG(LogUvrNetwork, Log, TEXT("Session thread %s finished"), *m_name);
	return 0;
}
