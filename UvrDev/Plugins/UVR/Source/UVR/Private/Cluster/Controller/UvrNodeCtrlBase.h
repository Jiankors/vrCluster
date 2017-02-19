// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

// Forward declarations
class UvrClusterManager;

class UvrNodeCtrlBase :
	public  IPUvrNodeController,
	private UvrNoncopyable,
	private UvrNonmoveable
{
	// This is needed to perform initialization from outside of constructor (polymorphic init)
	friend UvrClusterManager;

public:
	UvrNodeCtrlBase(const FString& ctrlName, const FString& nodeName);

	virtual ~UvrNodeCtrlBase() = 0
	{ }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrNodeController
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Initialize() override final;
	virtual void Release() override final;

	virtual bool IsMaster() const override final
	{ return !IsSlave(); }
	
	virtual bool IsCluster() const override final
	{ return !IsStandalone(); }

	virtual FString GetNodeId() const override final
	{ return m_nodeName; }

	virtual FString GetControllerName() const override final
	{ return m_ctrlName; }

protected:
	virtual bool InitializeStereo()
	{ return true; }

	virtual bool InitializeServers()
	{ return true; }

	virtual bool StartServers()
	{ return true; }

	virtual void StopServers()
	{ return; }

	virtual bool InitializeClients()
	{ return true; }

	virtual bool StartClients()
	{ return true; }
	
	virtual void StopClients()
	{ return; }

private:
	const FString m_nodeName;
	const FString m_ctrlName;
};

