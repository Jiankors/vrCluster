// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrSerializable.h"

class UvrMessage : IUvrSerializable
{
public:
	typedef TSharedPtr<UvrMessage> Ptr;
	typedef TMap<FString, FString> DataType;

public:
	UvrMessage();
	UvrMessage(const FString& name, const FString& type, const FString& protocol);

	UvrMessage(const UvrMessage&) = default;
	UvrMessage(UvrMessage&&)      = default;
	
	UvrMessage& operator= (const UvrMessage&) = default;
	UvrMessage& operator= (UvrMessage&&)      = default;
	
	virtual ~UvrMessage();

public:
	// Message head
	inline FString GetName()     const { return m_name; }
	inline FString GetType()     const { return m_type; }
	inline FString GetProtocol() const { return m_prot; }

	// Message custom data get/set
	template <typename ValType> bool GetArg(const FString& argName, ValType& argVal);
	template <typename ValType> void SetArg(const FString& argName, const ValType& argVal);

	// Get all arguments (be careful with the reference)
	const DataType& GetArgs() const
	{ return m_args; }

	void SetArgs(const DataType& data)
	{ m_args = data; }

	// Serialization
	virtual bool Serialize  (FMemoryWriter& ar) override;
	virtual bool Deserialize(FMemoryReader& ar) override;

	FString ToString() const;

private:
	inline bool ExtractKeyVal(const FString& pair, FString& key, FString& val);
	FString ArgsToString() const;

private:
	FString m_name;
	FString m_type;
	FString m_prot;

	DataType m_args;
};
