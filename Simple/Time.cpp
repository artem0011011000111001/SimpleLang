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
#ifdef __linux__
		localtime_r(&currentTime, &localTime);
#else
		localtime_s(&localTime, &currentTime);
#endif 

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

	DEF_STRUCT(Date)

	FIELD(L"year",   L"num", false, NOT_VALUE);
	FIELD(L"month",  L"num", false, NOT_VALUE);
	FIELD(L"day",    L"num", false, NOT_VALUE);
	FIELD(L"hour",   L"num", false, NOT_VALUE);
	FIELD(L"minute", L"num", false, NOT_VALUE);
	FIELD(L"second", L"num", false, NOT_VALUE);

	CONSTRUCTOR({

		fields[L"year"].value   = MOVE(args[0]);
		fields[L"month"].value  = MOVE(args[1]);
		fields[L"day"].value    = MOVE(args[2]);
		fields[L"hour"].value   = MOVE(args[3]);
		fields[L"minute"].value = MOVE(args[4]);
		fields[L"second"].value = MOVE(args[5]);

		}, 6)

	END_STRUCT(Date);
		

	//auto fields_params = DECL_FIELDS({
	//	{ L"year",	 FIELD(L"num") },
	//	{ L"month",  FIELD(L"num") },
	//	{ L"day",	 FIELD(L"num") },
	//	{ L"hour",	 FIELD(L"num") },
	//	{ L"minute", FIELD(L"num") },
	//	{ L"second", FIELD(L"num") }
	//	});
	/*Fields_decl_t DateFields = {
		{ L"year",	 FIELD(L"num") },
		{ L"month",  FIELD(L"num") },
		{ L"day",	 FIELD(L"num") },
		{ L"hour",	 FIELD(L"num") },
		{ L"minute", FIELD(L"num") },
		{ L"second", FIELD(L"num") }
	};*/

	/*static Fields_decl_t DateFields = DECL_FIELDS({
		{ L"year",	 FIELD(L"num") },
		{ L"month",  FIELD(L"num") },
		{ L"day",	 FIELD(L"num") },
		{ L"hour",	 FIELD(L"num") },
		{ L"minute", FIELD(L"num") },
		{ L"second", FIELD(L"num") }
	});*/


	/*DECL_FIELDS(DateFields, div({
		{ L"year",	 FIELD(L"num") },
		{ L"month",  FIELD(L"num") },
		{ L"day",	 FIELD(L"num") },
		{ L"hour",	 FIELD(L"num") },
		{ L"minute", FIELD(L"num") },
		{ L"second", FIELD(L"num") }
		}));*/

	//auto bbbb = BLOCK(args) {
	//	Vars_t fields;
	//	auto field_decl_it = DateFields.begin();  //// mnisdafysdgfuyas fields_params is null
	//	for (auto& arg : args) {

	//		if (arg->GetTypeInString() !=
	//			field_decl_it->second.type) throw Simple_Error("Invalid type");
	//		fields.emplace(field_decl_it->first, arg->clone());
	//		++field_decl_it;
	//	}
	//	return STRUCT(L"Date", fields);
	//};

	/*_DEFINE_STRUCT(L"Date", DECL_FIELDS({
		{ L"year",	 FIELD(L"num") },
		{ L"month",  FIELD(L"num") },
		{ L"day",	 FIELD(L"num") },
		{ L"hour",	 FIELD(L"num") },
		{ L"minute", FIELD(L"num") },
		{ L"second", FIELD(L"num") }
		}));*/

	//_DEFINE_STRUCT(L"Date", DateFields);

	/*_DEFINE_STRUCT(L"Date", DECL_FIELDS({
		{ L"year",	 FIELD(L"num") },
		{ L"month",  FIELD(L"num") },
		{ L"day",	 FIELD(L"num") },
		{ L"hour",	 FIELD(L"num") },
		{ L"minute", FIELD(L"num") },
		{ L"second", FIELD(L"num") }
		}));*/
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