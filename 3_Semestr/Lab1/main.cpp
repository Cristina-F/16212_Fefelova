#include "student.h"
#include "flat_map.h"
#include "gtest/gtest.h"

#define N 10
#define M 6

TEST( Flat_map_test, insert ) {
    Flat_map <std::string, struct value> fm(N);
    ASSERT_EQ( fm.size_(), N );
    for ( int i = 0;  i < N; i++ ) {
        ASSERT_EQ( fm.capacity_(), i );
        EXPECT_TRUE( fm.insert( std:: to_string( i ) , value( i, N * i ) ) );
        EXPECT_TRUE( fm.contains(std:: to_string( i ) ) );
        ASSERT_EQ( fm[std:: to_string(i)],  value( i, N * i ) );
    }
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

    }
    ASSERT_EQ(fm.capacity_(), 0);
}

TEST( Flat_map_test, empty ) {
    Flat_map <std::string, struct value> fm(N);
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
    ASSERT_EQ(fm.capacity_(), 0);
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
    for ( int i = 0;  i < N; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) );
    }
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
    for ( int i = 0;  i < N; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) ) ;
        EXPECT_TRUE( fm.contains(std:: to_string( i ) ) );
        ASSERT_EQ( fm[std:: to_string(i)],  value( i, N * i ) );
    }
}

TEST( Flat_map_test, at ) {
    Flat_map <std::string, struct value> fm(N);
    for ( int i = 0;  i < N; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) ) ;
    }
    for ( int i = 0;  i < N; i++ ) {
        ASSERT_NO_THROW( fm.at(std:: to_string( i ) ) );
        ASSERT_EQ( value( i, N * i ) , fm.at(std:: to_string( i ) ) );
    }
    ASSERT_ANY_THROW(fm.at( std:: to_string(N) ) );
}

TEST( Flat_map_test, square_brackets ) {
    Flat_map <std::string, struct value> fm(N);
    for ( int i = 0;  i < N - 1; i++ ) {
        fm.insert( std:: to_string( i ) , value( i, N * i ) ) ;
    }
    for ( int i = 0;  i < N - 1; i++ ) {
        ASSERT_EQ( fm[std:: to_string(i)], value( i, N * i )  );

    }
    ASSERT_EQ(fm[std:: to_string(N - 1)], value() );
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
    int n = max( N - 3, N);
    for ( int i = 0;  i < n; i++ ) {
        /*if ( !( ASSERT_EQ(a[std::to_string( i  )], b[std::to_string( i )]))) {
            break;
        }*/

    }
}

int main( int argc, char** argv ) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
