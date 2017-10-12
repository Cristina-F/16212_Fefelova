#include "student.h"
#include "flat_map.h"
#include "gtest/gtest.h"

#define N 10
#define M 6

TEST( Flat_map_test, insert ) {
    Flat_map <std::string, struct value> fm(1);

    ASSERT_EQ( fm.size_(), 1 );
    ASSERT_EQ( fm.capacity_(), 0 );

    ASSERT_TRUE( fm.insert( std::string("A"), value( 10, 20 ) ) );
    ASSERT_EQ( fm.capacity_(), 1 );
    ASSERT_TRUE( fm.contains(std::string("A") ) );
    ASSERT_EQ( fm[std::string("A")],  value( 10, 20 )  );

    EXPECT_EQ( fm.size_(), fm.capacity_() );
    ASSERT_TRUE( fm.insert( std::string("C"), value( 20, 30 ) ) );
    EXPECT_EQ( fm.size_(), 2 );
    ASSERT_EQ( fm.capacity_(), 2 );

    ASSERT_TRUE( fm.insert( std::string("B"), value( 30, 20 ) ) );
}

TEST( Flat_map_test, erase ) {
    Flat_map <std::string, struct value> fm(N);
    ASSERT_EQ( fm.size_(),  N);
    for ( int i = 0;  i < N; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) );
    }

    for( int i = 0; i < N; i++ ) {
        ASSERT_EQ( fm.capacity_(), N - i  );
        EXPECT_TRUE(fm.erase( std:: to_string(i) ) );
        EXPECT_FALSE(fm.contains(std:: to_string(i) ) );
        //std::cout<<"HH"<<std::endl;
    }
    ASSERT_EQ(fm.capacity_(), 0);
}

TEST( Flat_map_test, empty ) {
    Flat_map <std::string, struct value> fm(1);
    ASSERT_EQ(fm.capacity_(), 0);
    ASSERT_TRUE(fm.empty() );
}

TEST( Flat_map_test, clear ) {
    Flat_map <std::string, struct value> fm(N);
    ASSERT_EQ( fm.size_(),  N);
    for ( int i = 0;  i < N; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) );
    }
    fm.clear();
    ASSERT_TRUE(fm.empty() );
}

TEST( Flat_map_test, swap ) {
    Flat_map <std::string, struct value> a(N);
    Flat_map <std::string, struct value> b(M);
    for ( int i = 0;  i < N - 3; i++ ) {
        a.insert( std:: to_string( i ) , value( i, N * i ) );
    }
    for ( int i = 0;  i < M - 3; i++ ) {
        b.insert( std:: to_string( i * 10 ) , value( i * 10, M * i ) );
    }
    a.swap(b);
    ASSERT_EQ( a.size_(), M );
    ASSERT_EQ( b.size_(), N );
    ASSERT_EQ( a.capacity_(), M - 3 );
    ASSERT_EQ( b.capacity_(), N - 3);
    for ( int i = 0;  i < N - 3; i++ ) {
        ASSERT_EQ(b[std:: to_string( i )], value( i, N * i ));

    }
    for ( int i = 0;  i < M - 3; i++ ) {
        ASSERT_EQ(a[std:: to_string( i * 10 )], value( i * 10, M * i ));
    }
}

TEST( Flat_map_test, size_ ) {
    Flat_map <std::string, struct value> fm(N);
    ASSERT_EQ( fm.size_(), N );
}

TEST( Flat_map_test, capacity_ ) {
    Flat_map <std::string, struct value> fm(N);
    for ( int i = 0;  i < N - 3; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) );
    }
    ASSERT_EQ( fm.capacity_(), N - 3 );
}

TEST( Flat_map_test, contains ) {
    Flat_map <std::string, struct value> fm(N);
    fm.insert( std:: string("A"), value( 10, 15 ));
    ASSERT_TRUE( fm.contains(std:: string("A") ) );
    ASSERT_EQ( fm[std:: string("A")],  value( 10, 15 ) );
}

TEST( Flat_map_test, at ) {
    Flat_map <std::string, struct value> fm(1);
    fm.insert( std:: string("A"), value( 10, 15 ));
    ASSERT_NO_THROW( fm.at(std:: string("A")) );
    ASSERT_EQ( value( 10, 15 ), fm.at(std:: string("A") ) );
    ASSERT_ANY_THROW(fm.at( std:: string("B") ) );
}

TEST( Flat_map_test, square_brackets ) {
    Flat_map <std::string, struct value> fm(1);
    fm.insert( std:: string("A") , value( 10, 15 ) ) ;
    ASSERT_EQ( fm[std:: string("A")], value( 10, 15 )  );
    ASSERT_EQ(fm[std:: string("B")], value() );
}

TEST( Flat_map_test, assign ) {
    Flat_map <std::string, struct value> a(N);
    Flat_map <std::string, struct value> b(M);
    for ( int i = 0;  i < N - 3; i++ ) {
        a.insert( std:: to_string( i ) , value( i, N * i ) );
    }
    for ( int i = 0;  i < M - 3; i++ ) {
        b.insert( std:: to_string( i * 10 ) , value( i * 10, M * i ) );
    }
    a = b;
    ASSERT_EQ( a.size_(), M );
    ASSERT_EQ( a.capacity_(), M - 3 );
    for ( int i = 0;  i < M - 3; i++ ) {
        ASSERT_EQ(a[std::to_string( i * 10 )], b[std::to_string( i * 10 )]);
    }
}

TEST( Flat_map_test, equally ) {
    Flat_map <std::string, struct value> a(N);
    Flat_map <std::string, struct value> b(N);
    for ( int i = 0;  i < N - 3; i++ ) {
        a.insert( std:: to_string( i ) , value( i, N * i ) );
    }
    for ( int i = 0;  i < N - 3; i++ ) {
        b.insert( std:: to_string( i  ) , value( i , N * i ) );
    }
    ASSERT_TRUE(a == b );
    ASSERT_EQ( a.size_(), b.size_() );
    ASSERT_EQ( a.capacity_(), b.capacity_() );
    for ( int i = 0;  i < N - 3; i++ ) {
        ASSERT_EQ(a[std::to_string( i  )], b[std::to_string( i )]);
    }
}

TEST( Flat_map_test, not_equally ) {
    Flat_map <std::string, struct value> a(N);
    Flat_map <std::string, struct value> b(M);
    for ( int i = 0;  i < N - 3; i++ ) {
        a.insert( std:: to_string( i ) , value( i, N * i ) );
    }
    for ( int i = 0;  i < M - 3; i++ ) {
        b.insert( std:: to_string( i * 10 ) , value( i * 10, M * i ) );
    }
    ASSERT_TRUE(a != b );
    ASSERT_FALSE( a == b );
}

int main( int argc, char** argv ) {
    ::testing::InitGoogleTest(&argc, argv);
   /* Flat_map <std::string, struct value> a(5);
    a.insert( std::string("A"), value( 20, 30 ) );
    a.insert( std::string("Cab"), value( 20, 30 ) );
    a.insert( std::string("D"), value( 20, 30 ) );
    a.insert( std::string("Cagb"), value( 20, 30 ) );
    a.insert( std::string("Bg"), value( 20, 30 ) );
    a.insert( std::string("Cfffagb"), value( 20, 30 ) );
    a.print();*/
    return RUN_ALL_TESTS();
}
