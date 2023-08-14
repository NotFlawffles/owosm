#pragma once

#include <string>
#include <map>
#include <vector>
#include "opcodes.h"
#include "lexer.h"
#include "token.h"

class Generator {
    Lexer lexer;
    Token current;

    std::map<std::string, i16> lookupTable = {
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
        {"alloc", Alloc},     {"allocz", Allocz},     {"allocc", Allocc},     {"allocv", Allocv}
    };

    i16 generateNext(void);

    public:
    Generator(std::string fileName, std::string content);
    void generate(void);
};
