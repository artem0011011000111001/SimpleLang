#include "Time.h"

#include <chrono>
#include <thread>

using namespace Simple;

void Simple_libs::Time::Time::Init() {
	InitStructs();
	InitVars();
	InitFuncs();
}

void Simple_libs::Time::Time::InitVars() {

}

void Simple_libs::Time::Time::InitFuncs() {
	_DEFINE_FUNCTION(L"now", BLOCK(args) {
		return NUMBER(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count());
		}, 0);

	static auto _system_now = [](Args_t args) -> VALUE {
		auto now = std::chrono::system_clock::now();

		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

		std::tm localTime;
		localtime_s(&localTime, &currentTime);

		VALUE year   = NUMBER(localTime.tm_year + 1900); // To solve the problem of calling the copy constructor from the vector
		VALUE month  = NUMBER(localTime.tm_mon + 1);
		VALUE day    = NUMBER(localTime.tm_mday);
		VALUE hour   = NUMBER(localTime.tm_hour);
		VALUE minute = NUMBER(localTime.tm_min);
		VALUE second = NUMBER(localTime.tm_sec);

		Args_t _Date_args;
		_Date_args.push_back(std::move(year));
		_Date_args.push_back(std::move(month));
		_Date_args.push_back(std::move(day));
		_Date_args.push_back(std::move(hour));
		_Date_args.push_back(std::move(minute));
		_Date_args.push_back(std::move(second));	// Decided

		VALUE temp = CALL(L"Date", MOVE(_Date_args))/*HAND_OVER_ARGS(
			NUMBER(localTime.tm_year + 1900),
			(ValuePtr)NUMBER(localTime.tm_mon + 1),
			(ValuePtr)NUMBER(localTime.tm_mday),
			(ValuePtr)NUMBER(localTime.tm_hour),
			(ValuePtr)NUMBER(localTime.tm_min),
			(ValuePtr)NUMBER(localTime.tm_sec)
		)*/;	
		return MOVE(temp);
		};

	_DEFINE_FUNCTION(L"system_now", _system_now, 0);

	_DEFINE_FUNCTION(L"sleep", BLOCK(args) {
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(args.front()->AsDouble()));
		return VOID;
	}, 1);
}

void Simple_libs::Time::Time::InitStructs() {

	_DEFINE_STRUCT(L"Date", FIELD_DECL(
		fields.emplace(L"year",   FIELD(L"num")),
		fields.emplace(L"month",  FIELD(L"num")),
		fields.emplace(L"day",    FIELD(L"num")),
		fields.emplace(L"hour",   FIELD(L"num")),
		fields.emplace(L"minute", FIELD(L"num")),
		fields.emplace(L"second", FIELD(L"num"))
	));
}

//VALUE Simple_libs::Time::Time::_Date(Args_t args) {
//
//	Val_map fields;
//	Fields_decl_t fields_decl = {
//		{ "year" , ValueType::_NUMBER },
//		{ "month" , ValueType::_NUMBER },
//		{ "day" , ValueType::_NUMBER },
//		{ "hour" , ValueType::_NUMBER },
//		{ "minute" , ValueType::_NUMBER },
//		{ "second" , ValueType::_NUMBER }
//	};
//
//	auto fields_decl_it = fields_decl.begin();
//	for (auto& arg : args) {
//
//		if (arg->GetType() != ValueType::_NUMBER)
//			throw Simple_Error("Invalid type"); // 
//
//		fields.emplace(fields_decl_it->first, arg->clone());
//
//		++fields_decl_it;
//	}
//	Structs::Add("Date", fields_decl);
//	return STRUCT("Date", fields);
//}