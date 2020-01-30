#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>

#include "tritset.h"

TEST_CASE("Test_1", "Trim1") {

	std::stringstream out;

    Tritset set;

    set[54] = Trit::T;
    set.trim(25);
    set.print(out);

	REQUIRE (out.str() == "Tritset is empty\n");
}

TEST_CASE("Test_11", "Trim2") {

    std::stringstream out;

	Tritset set = {Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    set.trim(3);
    set.print(out);

	REQUIRE (out.str() == "T U F \n");
	REQUIRE (set.length() == 3);
}

TEST_CASE("Test_2", "Cardinality1") {

    Tritset set = {Trit::T, Trit::U, Trit::F, Trit::T, Trit::F, Trit::F, Trit::T, Trit::U, Trit::F, Trit::T, Trit::U,
                   Trit::F, Trit::T, Trit::F, Trit::F, Trit::T, Trit::U, Trit::F,};

	REQUIRE (set.cardinality(Trit::F) == 8);
	REQUIRE (set.cardinality(Trit::U) == 4);
	REQUIRE (set.cardinality(Trit::T) == 6);	
}

TEST_CASE("Test_3", "Cardinality2") {

    Tritset set = {Trit::T, Trit::U, Trit::F, Trit::T, Trit::F, Trit::F, Trit::T, Trit::U, Trit::F, Trit::T, Trit::U,
                   Trit::F, Trit::T, Trit::F, Trit::F, Trit::T, Trit::U, Trit::F,};

    std::unordered_map<Trit, int> map = set.cardinality();

	REQUIRE (map[Trit::F] == 8);
	REQUIRE (map[Trit::U] == 4);
	REQUIRE (map[Trit::T] == 6);
}

TEST_CASE("Test_10", "Cardinality3") {

    Tritset set{Trit::T, Trit::U, Trit::T};

    std::unordered_map<Trit, int> map = set.cardinality();

	REQUIRE (map[Trit::F] == 0);
}

TEST_CASE("Test_4", "capacity1") {

    Tritset set(1000);
    REQUIRE (set.get_capacity() >= 1000*2 / 8 / sizeof(unsigned int));
}

TEST_CASE("Test_5", "capacity2") {

    Tritset set;
    set[10000] = Trit::U;
    REQUIRE (set.get_capacity() == 0);
}

TEST_CASE("Test_6", "capacity3") {

    Tritset set;
    set[100] = Trit::T;
    REQUIRE (set.get_capacity() >= 100*2 / 8 / sizeof(unsigned int));
}

TEST_CASE("Test_7", "initialization1") {

	std::stringstream out;

    Tritset set{Trit::F, Trit::U, Trit::T,Trit::F, Trit::F, Trit::T,Trit::F, Trit::T, Trit::T};
    set.print(out);

    REQUIRE (out.str() == "F U T F F T F T T \n");
}

TEST_CASE("Test_8", "lenght1") {

    Tritset set;
    set[54] = Trit::F;
    set[57] = Trit::U;

    REQUIRE (set.length() == 55);
}

TEST_CASE("Test_9", "lenght2") {

    Tritset set;

    REQUIRE (set.length() == 0);
}

TEST_CASE("Test_12", "operator&") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::T, Trit::T, Trit::F, Trit::F, Trit::F};
    Tritset result;

    result = set1 & set2;
    result.print(out);

    REQUIRE (out.str() == "F U T F F F \n");
}

TEST_CASE("Test_13", "operator=&") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::T, Trit::T, Trit::F, Trit::F, Trit::F};

    set1 &= set2;
    set1.print(out);

    REQUIRE (out.str() == "F U T F F F \n");
}

TEST_CASE("Test_14", "operator|") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::T, Trit::T, Trit::F, Trit::F, Trit::F};
    Tritset result;

    result = set1 | set2;
    result.print(out);

    REQUIRE (out.str() == "T T T F U T \n");
}

TEST_CASE("Test_15", "operator=|") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::T, Trit::T, Trit::F, Trit::F, Trit::F};

    set1 |= set2;
    set1.print(out);

    REQUIRE (out.str() == "T T T F U T \n");
}

TEST_CASE("Test_16", "operator!") {

	std::stringstream out;

    Tritset set{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
   
    (!set).print(out);

    REQUIRE (out.str() == "T U F T U F \n");
}

TEST_CASE("Test_17", "operator==") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    bool result = (set1 == set2);

    REQUIRE (result == false);
}

TEST_CASE("Test_18", "operator==") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    bool result = (set1 == !set2);

    REQUIRE (result == true);
}

TEST_CASE("Test_19", "operator!=") {

	std::stringstream out;

    Tritset set1{Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    Tritset set2{Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    bool result = (set1 != set2);

    REQUIRE (result == true);
}

TEST_CASE("Test_20", "operator=") {

    Tritset set1(1000);
    Tritset set2(2000);

    set1 = {Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};
    set2 = {Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    Tritset result = set1 & set2;

    REQUIRE (set2.get_capacity() == result.get_capacity());
}


TEST_CASE("Test_21", "foreach1") {

	std::stringstream out;

    Tritset set1 = {Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};

        for(auto x : set1)
    {
        printTrit(x, out);
    }

    REQUIRE (out.str() == "F U T F U T ");
} 


TEST_CASE("Test_22", "foreach2") {

	std::stringstream out;

    Tritset set1 = {Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T};

        for (Iterator it = set1.begin() ; it != set1.end(); ++it)
    {
        it = Trit::T;
    }

        for(auto x : set1)
    {
        printTrit(x, out);
    }

    REQUIRE (out.str() == "T T T T T T ");
}

TEST_CASE("Test_23", "operator[]") {

    std::stringstream out;

    Tritset set1;
    Tritset set2 = {Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    set1[545] = set2[3];

    printTrit(set1[545], out);

    REQUIRE (out.str() == "T ");
}

TEST_CASE("Test_24", "copy") {

    std::stringstream out;

    Tritset set1 = {Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::U};
    Tritset set2 = set1;

    printTrit(set1[3], out);

    REQUIRE (out.str() == "F ");
}

TEST_CASE("Test_25", "shrink") {

	std::stringstream out;

    Tritset set = {Trit::T, Trit::U, Trit::F, Trit::T, Trit::U, Trit::F};

    set[100] = Trit::T;
    set.delete_trit(100);
    set.shrink();

    REQUIRE (set.get_capacity() == 16);
}

TEST_CASE("Test_26", "copy") {

    std::stringstream out;

    Tritset set1 = {Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::U};
    Tritset set2 = set1;

    set2.print(out);

    REQUIRE (out.str() == "F U T F \n");
}

TEST_CASE("Test_27", "copy") {

    std::stringstream out;

    const Tritset a{Trit::U, Trit::U, Trit::U, Trit::T, Trit::T, Trit::T, Trit::F, Trit::F, Trit::F};
    const Tritset b{Trit::U, Trit::T, Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T, Trit::F};
    const Tritset aandb{Trit::U, Trit::U, Trit::F, Trit::U, Trit::T, Trit::F, Trit::F, Trit::F, Trit::F};

    Tritset a1 = a;
    a1 &= b;

    REQUIRE (a1 == aandb);
}