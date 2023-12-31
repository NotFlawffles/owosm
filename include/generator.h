#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "opcodes.h"
#include "lexer.h"
#include "token.h"

class Generator {
    Lexer lexer;
    Token current;
    std::vector<u16> program;

    std::unordered_map<std::string, u16> labels;

    std::unordered_map<std::string, u16> lookupTable = {
        {"swp", Swp},         {"swpz", Swpz},         {"swpc", Swpc},         {"swpv", Swpv},
        {"add", Add},         {"addz", Addz},         {"addc", Addc},         {"addv", Addv},
        {"sub", Sub},         {"subz", Subz},         {"subc", Subc},         {"subv", Subv},
        {"mul", Mul},         {"mulz", Mulz},         {"mulc", Mulc},         {"mulv", Mulv},
        {"div", Div},         {"divz", Divz},         {"divc", Divc},         {"divv", Divv},
        {"and", And},         {"andz", Andz},         {"andc", Andc},         {"andv", Andv},
        {"or",  Or},          {"orz", Orz},           {"orc", Orc},           {"orv", Orv},
        {"xor", Xor},         {"xorz", Xorz},         {"xorc", Xorc},         {"xorv", Xorv},
        {"not", Not},         {"notz", Notz},         {"notc", Notc},         {"notv", Notv},
        {"lsl", Lsl},         {"lslz", Lslz},         {"lslc", Lslc},         {"lslv", Lslv},
        {"lsr", Lsr},         {"lsrz", Lsrz},         {"lslc", Lsrc},         {"lsrv", Lsrv},
        {"mod", Mod},         {"modz", Modz},         {"modc", Modc},         {"modv", Modv},
        {"cmp", Cmp},         {"cmpz", Cmpz},         {"cmpc", Cmpc},         {"cmpv", Cmpv},
        {"jump", Jump},       {"jumpz", Jumpz},       {"jumpc", Jumpc},       {"jumpv", Jumpv},
        {"pop", Pop},         {"popz", Popz},         {"popc", Popc},         {"popv", Popv},
        {"syscall", Syscall}, {"syscallz", Syscallz}, {"syscallc", Syscallc}, {"syscallv", Syscallv},
        {"alloc", Alloc},     {"allocz", Allocz},     {"allocc", Allocc},     {"allocv", Allocv},
        {"str", Str},         {"strz", Strz},         {"strc", Strc},         {"strv", Strv},
        {"ld", Ld},           {"ldz", Ldz},           {"ldc", Ldc},           {"ldv", Ldv},
        {"dbg", Dbg},
        {"ret", Ret},         {"retz", Retz},         {"retc", Retc},         {"retv", Retv},
        {"dup", Dup},         {"dupz", Dupz},         {"dupc", Dupc},         {"dupv", Dupv},
        {"b", B},             {"bz", Bz},             {"bc", Bc},             {"bv", Bv},
        {"set", Set},         {"setz", Setz},         {"setc", Setc},         {"setv", Setv},
        {"get", Get},         {"getz", Getz},         {"getc", Getc},         {"getv", Getv},
        {"inc", Inc},         {"incz", Incz},         {"incc", Incc},         {"incv", Incv},
        {"dec", Dec},         {"decz", Decz},         {"decc", Decc},         {"decv", Decv}
    };

    u16 generateNext(void);
    u16 generateInteger(void);
    void generateLabel(void);
    void generateString(void);
    void preprocess(void);
    std::string getOutName(void);

    public:
    Generator(std::string fileName, std::string content);
    void generate(void);
};
