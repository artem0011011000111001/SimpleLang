#include "AST.h"
#include "Utils.h"
#include "Variables.h"

using namespace Simple;

TryCatchStatement::TryCatchStatement(StatementPtr tryBlock, const String& key, bool isConst, const String& type_in_str
	, StatementPtr catchBlock) : tryBlock(std::move(tryBlock)), key(key), isConst(isConst), type_in_str(type_in_str), catchBlock(std::move(catchBlock)) {}

void TryCatchStatement::execute(){
	try {
		Variables::PushState();
		tryBlock->execute();
		Variables::PopState();
	}
	catch (ValuePtr& ThrowValue) {
		Variables::PopState();

		if (equals_type(type_in_str, ThrowValue->GetTypeInString())) {
			//if (Variables::IsExist(key))
			Variables::PushState();
			Variable SaveGlobalMatchWithInitNameValue;

			if (Variables::IsExist(key))
				SaveGlobalMatchWithInitNameValue = Variable(Variables::Get(key), Variables::IsConstant(key));

			Variables::Set(key, Variable(std::move(ThrowValue), isConst));

			catchBlock->execute();

			if (SaveGlobalMatchWithInitNameValue.value)
				Variables::Set(key, std::move(SaveGlobalMatchWithInitNameValue));

			Variables::PopState();
		}
		else throw ThrowValue->clone();
	}
}