#include "AST.h"
#include "Utils.h"
#include "Variables.h"

using namespace Simple;

TryCatchStatement::TryCatchStatement(StatementPtr tryBlock, const WStr_vec& keys, Vec<bool> isConsts, const WStr_vec& types_in_str, Vec<StatementPtr> catchBlocks, StatementPtr finally_block)
	: tryBlock(MOVE(tryBlock)), keys(keys), isConsts(isConsts), types_in_str(types_in_str), catchBlocks(MOVE(catchBlocks)), finally_block(MOVE(finally_block)) {}

void TryCatchStatement::execute(){
	try {
		Variables::PushState();
		tryBlock->execute();
		Variables::PopState();
	}
	catch (ValuePtr& ThrowValue) {
		Variables::PopState();
		
		auto types_in_str_it = types_in_str.begin();
		auto keys_it		 = keys.begin();
		auto isConsts_it	 = isConsts.begin();

		for (auto& catchBlock : catchBlocks) {

			if (equals_type(*types_in_str_it, ThrowValue->GetTypeInString())) {

				Variables::PushState();
				Variables::PushMatches(*keys_it, Variable(Variables::Get(*keys_it), Variables::IsConstant(*keys_it)));

				Variables::Set(*keys_it, Variable(MOVE(ThrowValue), *isConsts_it));

				catchBlock->execute();

				Variables::PopMatches();
				Variables::PopState();
				return;
			}
			++types_in_str_it;
			++keys_it;
			++isConsts_it;
		}
		if (finally_block) {
			Variables::PushState();

			finally_block->execute();

			Variables::PopState();
		}

		else throw ThrowValue->clone();
	}
}