#include "AST.h"
#include "Method_info.h"
#include "Functions.h"
#include "Field_info.h"
#include "ArgParams.h"

using namespace Simple;

ClassDefineStatement::ClassDefineStatement(const WString& name, RawClassFields_decl_t fields_params, RawMethod_decl_t methods_params)
	: name(name), fields_params(MOVE(fields_params)), methods_params(MOVE(methods_params)) {}

void ClassDefineStatement::execute() {
	fields = RawToMade(this->fields_params);

	static Fields_decl_t RawFields_params;
	
	for (auto& field : this->fields) {
		RawFields_params.emplace(field.first, field.second.first.clone());
	}
	
	/*for (auto& method : methods_params) {
		if (method.first == L"constructor") {

			for (auto& constructor : method.second) {

				auto& Method_info = constructor.second;
				
				Functions::RegisterDynamicFunction(name,
					Statement_to_class_constructor(Method_info.body, Method_info.args_params, Method_info.is_any_args, RawFields_params, methods_params, name),
					{ Method_info.is_any_args ? any_args : (int)constructor.first });
			}

		}
	}*/
	static Vec<StatementPtr> bodies;
	int i = 0;

	for (auto& [key, methods] : methods_params) {
		if (key == L"constructor") {
			for (auto& [args_count, method_info] : methods) {

				bodies.push_back(MOVE(method_info.body));

				auto func = Statement_to_class_constructor(
					bodies[i],
					method_info.args_params,
					method_info.is_any_args,
					RawFields_params,
					methods_params,
					name
				);
				++i;

				// Регистрация функции
				Functions::RegisterDynamicFunction(
					name,
					func,
					(int)method_info.args_params.size()
				);
			}
		}
	}
}