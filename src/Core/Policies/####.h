#pragma once

#define CYDL_POLICY_NAME policy_test

struct AccPolicy
{
	struct AccuTypeCate
	{
		struct Add;
		struct Mul;
	};

	using Accu = AccuTypeCate::Add;

	struct IsAveValueCate;
	static constexpr bool IsAve = false;

	struct ValueTypeCate;
	using Value = float;
};