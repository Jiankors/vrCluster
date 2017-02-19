// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Network/UvrMessage.h"

struct IPUvrNodeController;


class UvrClusterManager :
	public  IPUvrClusterManager,
	private UvrNoncopyable,
	private UvrNonmoveable
{
public:
	UvrClusterManager();
	virtual ~UvrClusterManager();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Init() override;
	virtual void Release() override;
	virtual bool StartSession(const FString& configPath) override;
	virtual void EndSession() override;
	virtual bool StartGame(UWorld* pWorld) override;
	virtual void EndGame() override;
	virtual void PreTick(float DeltaSeconds) override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrClusterManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool IsMaster()     const override;
	virtual bool IsSlave()      const override;
	virtual bool IsStandalone() const override;
	virtual bool IsCluster()    const override;

	virtual FString GetNodeId() const override
	{ return m_nodeId; }

	virtual uint32 GetNodesAmount() const override
	{ return m_nodesAmount; }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrClusterManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual IPUvrNodeController* GetController() const override;

	virtual float GetDeltaTime() const override
	{ return m_deltaTime; }

	virtual void  SetDeltaTime(float deltaTime) override
	{ m_deltaTime = deltaTime; }

	virtual void RegisterSyncObject(IUvrClusterSyncObject* pSyncObj) override;
	virtual void UnregisterSyncObject(IUvrClusterSyncObject* pSyncObj) override;

	virtual void ExportSyncData(UvrMessage::DataType& data) const override;
	virtual void ImportSyncData(const UvrMessage::DataType& data) override;

	virtual void SyncObjects() override;
	virtual void SyncInput()   override;

private:
	bool GetResolvedNodeId(FString& id) const;

	typedef TUniquePtr<IPUvrNodeController> TController;

	// Factory method
	TController CreateController() const;

private:
	// Controller implementation
	TController m_controller;
	mutable FCriticalSection m_lock;

	// Cluster/node props
	FString m_nodeId;
	uint32 m_nodesAmount = 0;

	// Current time delta for sync
	float m_deltaTime = 0.f;

	// Sync transforms
	TSet<IUvrClusterSyncObject*>   m_objects;
	mutable FCriticalSection       m_cs_objects;
	mutable UvrMessage::DataType   m_objectsCache;
};

