// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrMessage.h"


UvrMessage::UvrMessage()
{
}

UvrMessage::UvrMessage(const FString& name, const FString& type, const FString& protocol) :
	m_name(name),
	m_type(type),
	m_prot(protocol)
{
}

UvrMessage::~UvrMessage()
{
}


bool UvrMessage::Serialize(FMemoryWriter& ar)
{
	// Header
	ar << m_name;
	ar << m_type;
	ar << m_prot;

	TArray<FString> keys;
	m_args.GenerateKeyArray(keys);

	// Arguments amount
	FString strArgAmount = FString::FromInt(m_args.Num());
	ar << strArgAmount;

	// Arguments
	for (int i = 0; i < keys.Num(); ++i)
	{
		ar << keys[i];
		ar << m_args[keys[i]];
	}

	return true;
}

bool UvrMessage::Deserialize(FMemoryReader& ar)
{
	// Header
	ar << m_name;
	ar << m_type;
	ar << m_prot;

	// Arguments amount
	FString strArgsAmount;
	ar << strArgsAmount;
	const int32 amount = FCString::Atoi(*strArgsAmount);
	check(amount >= 0);
	
	// Arguments
	for (int32 i = 0; i < amount; ++i)
	{
		FString key;
		FString val;

		ar << key;
		ar << val;

		m_args.Add(key, val);
	}

	UE_LOG(LogUvrNetworkMsg, VeryVerbose, TEXT("Deserialized message: %s"), *ToString());

	return true;
}

FString UvrMessage::ToString() const
{
	return FString::Printf(TEXT("<prot=%s type=%s name=%s args={%s}>"), *GetProtocol(), *GetType(), *GetName(), *ArgsToString());
}

FString UvrMessage::ArgsToString() const
{
	FString str;
	str.Reserve(512);
	
	for (auto it = m_args.CreateConstIterator(); it; ++it)
		str += FString::Printf(TEXT("%s=%s "), *it->Key, *it->Value);

	return str;
}


template <typename ValType>
bool UvrMessage::GetArg(const FString& argName, ValType& argVal)
{
	if (m_args.Contains(argName))
	{
		FString strVal = m_args[argName];
		argVal = UvrTypesConverter::FromString<ValType>(strVal);
		return true;
	}
	return false;
}

template <typename ValType>
void UvrMessage::SetArg(const FString& argName, const ValType& argVal)
{
	m_args.Add(argName, UvrTypesConverter::ToString<ValType>(argVal));
}

