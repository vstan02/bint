/* BintTest - Tests for Bint
 * Copyright (C) 2021 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Bint.
 *
 * Bint is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include "Bint.hpp"

TEST(Bint, Bint) {
    ASSERT_EQ(Bint(), Bint(0));
    ASSERT_EQ(Bint(-0), Bint(0));
    ASSERT_EQ(Bint("0"), Bint(-0));
    ASSERT_EQ(Bint("-0"), Bint("0"));
    ASSERT_EQ(Bint(438), Bint("438"));
    ASSERT_EQ(Bint(-326), Bint("-326"));

    ASSERT_TRUE(Bint("-54") < 0);
    ASSERT_TRUE(Bint(56) < 76);
    ASSERT_TRUE(-Bint(54) < 0);
    ASSERT_FALSE(Bint() < -43);
    ASSERT_FALSE(Bint("-0") < 0);
    ASSERT_FALSE(Bint(-54) < -Bint(54));
}

TEST(Bint, size) {
    ASSERT_EQ(Bint(132).size(), 3);
    ASSERT_EQ(Bint(-132).size(), 3);
    ASSERT_EQ(Bint("0").size(), 1);
    ASSERT_EQ(Bint("-0").size(), 1);
    ASSERT_EQ(Bint().size(), 1);
    ASSERT_EQ(Bint("-238").size(), 3);
}

TEST(Bint, abs) {
    ASSERT_EQ(Bint(132).abs(), 132);
    ASSERT_EQ(Bint(-132).abs(), 132);
    ASSERT_EQ(Bint("0").abs(), 0);
    ASSERT_EQ(Bint("-0").abs(), 0);
    ASSERT_EQ(Bint().abs(), 0);
    ASSERT_EQ(Bint("-238").abs(), 238);
}

TEST(Bint, odd) {
    ASSERT_TRUE(Bint(133).odd());
    ASSERT_TRUE(Bint(-103).odd());
    ASSERT_TRUE(Bint("-23").odd());
    ASSERT_FALSE(Bint().odd());
    ASSERT_FALSE(Bint(132).odd());
    ASSERT_FALSE(Bint("32").odd());
}

TEST(Bint, even) {
    ASSERT_TRUE(Bint().even());
    ASSERT_TRUE(Bint(132).even());
    ASSERT_TRUE(Bint("32").even());
    ASSERT_FALSE(Bint(133).even());
    ASSERT_FALSE(Bint(-103).even());
    ASSERT_FALSE(Bint("-23").even());
}

TEST(Bint, prime) {
    ASSERT_TRUE(Bint(2).prime());
    ASSERT_TRUE(Bint(17).prime());
    ASSERT_TRUE(Bint("11").prime());
    ASSERT_FALSE(Bint().prime());
    ASSERT_FALSE(Bint(10).prime());
    ASSERT_FALSE(Bint(15).prime());
    ASSERT_FALSE(Bint(-103).prime());
    ASSERT_FALSE(Bint("-23").prime());
}

TEST(Bint, __PLUS__) {
    ASSERT_EQ(Bint() + 4354, 4354);
    ASSERT_EQ(Bint(23) + 54, 77);
    ASSERT_EQ(Bint(-132) + 43, -89);
    ASSERT_EQ(Bint("-324") + 324, 0);
}

TEST(Bint, __MINUS__) {
    ASSERT_EQ(Bint() - 4354, -4354);
    ASSERT_EQ(Bint(77) - 54, 23);
    ASSERT_EQ(Bint(-89) - 43, -132);
    ASSERT_EQ(Bint("-0") - 324, -324);
}

TEST(Bint, __MUL__) {
    ASSERT_EQ(Bint() * 4354, 0);
    ASSERT_EQ(Bint(32) * 2, 64);
    ASSERT_EQ(Bint(-11) * 11, -121);
    ASSERT_EQ(Bint("-2") * 54, -108);
}

TEST(Bint, __DIV__) {
    ASSERT_EQ(Bint() / 43, 0);
    ASSERT_EQ(Bint(2) / 23, 0);
    ASSERT_EQ(Bint(32) / 2, 16);
    ASSERT_EQ(Bint(-121) / 11, -11);
    ASSERT_EQ(Bint("-108") / -54, 2);
    ASSERT_THROW(Bint(34) / 0, std::runtime_error);
}

TEST(Bint, __MOD__) {
    ASSERT_EQ(Bint() % 43, 0);
    ASSERT_EQ(Bint(2) % 23, 2);
    ASSERT_EQ(Bint(35) % 2, 1);
    ASSERT_EQ(Bint(-123) % 11, -2);
    ASSERT_EQ(Bint("-108") % -54, 0);
    ASSERT_THROW(Bint(34) % 0, std::runtime_error);
}
