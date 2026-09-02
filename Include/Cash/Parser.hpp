#pragma once

#include <Cash/Ast.hpp>
#include <Cash/Token.hpp>

#include <Melon/Vector.hpp>
#include <Melon/Typing.hpp>

namespace Cash
{
        class Parser
        {
                ast_t nodes;
                tokens_t tokens;
                NodeAllocator node_allocator;
                Melon::Typing::USize token_cursor;
                Melon::Typing::USize node_cursor;

        public:
                Parser() = default;
                Parser(const tokens_t &tokens);

                void parse(this Parser &self);
                NodeDecl *parseDecl(this Parser &self);
                NodeVarDecl *parseVarDecl(this Parser &self);
                NodeExpr *parseExpr(this Parser &self);
                NodeExpr *parseTerm(this Parser &self);
                NodeExpr *parsePrimaryExpr(this Parser &self);
                NodeUnaryOp *parseUnaryOp(this Parser &self);
                NodeInteger *parseInteger(this Parser &self);
                NodeName *parseName(this Parser &self);

                void reset(this Parser &self);
                void setTokens(this Parser &self, const tokens_t &new_tokens);
        
                const ast_t &getNodes(this const Parser &self);
        };
} // namespace Cash