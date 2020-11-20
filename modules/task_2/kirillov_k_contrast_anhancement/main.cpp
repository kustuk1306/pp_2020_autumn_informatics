// Copyright 2020 Kirillov Konstantin
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include<iostream>
#include "./contrast_enhancement.h"
TEST(Parallel_Operations_MPI, Test_Matrix_11x3) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 11;
    int cols = 3;
    double alpha = 1.5;
    int beta = 1;
    Matrix global_mat(rows, std::vector<int>(cols));
    Matrix local_mat(rows, std::vector<int>(cols));
    global_mat = getRandomMatrix(rows, cols);
    if (procRank == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                local_mat[i][j] = global_mat[i][j];
                local_mat[i][j] = getSequentialContrast(local_mat, i, j, alpha, beta);
            }
        }
    }
    global_mat = getParallelContrast(global_mat, rows, cols, alpha, beta);
    if (procRank == 0) {
    int tmp = 0;
        for (int  i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (local_mat[i][j] == global_mat[i][j]) tmp++;
            }
        }
    bool check = 0;
    if (tmp == (rows*cols)) check = 1;
    ASSERT_EQ(check, 1);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix_17x5) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 17;
    int cols = 5;
    double alpha = 1.5;
    int beta = 1;
    Matrix global_mat(rows, std::vector<int>(cols));
    Matrix local_mat(rows, std::vector<int>(cols));
    global_mat = getRandomMatrix(rows, cols);
    if (procRank == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                local_mat[i][j] = global_mat[i][j];
                local_mat[i][j] = getSequentialContrast(local_mat, i, j, alpha, beta);
            }
        }
    }
    global_mat = getParallelContrast(global_mat, rows, cols, alpha, beta);
    if (procRank == 0) {
    int tmp = 0;
        for (int  i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (local_mat[i][j] == global_mat[i][j]) tmp++;
            }
        }
    bool check = 0;
    if (tmp == (rows*cols)) check = 1;
    ASSERT_EQ(check, 1);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix_100x97) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 100;
    int cols = 97;
    double alpha = 1.5;
    int beta = 1;
    Matrix global_mat(rows, std::vector<int>(cols));
    Matrix local_mat(rows, std::vector<int>(cols));
    global_mat = getRandomMatrix(rows, cols);
    if (procRank == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                local_mat[i][j] = global_mat[i][j];
                local_mat[i][j] = getSequentialContrast(local_mat, i, j, alpha, beta);
            }
        }
    }
    global_mat = getParallelContrast(global_mat, rows, cols, alpha, beta);
    if (procRank == 0) {
    int tmp = 0;
        for (int  i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (local_mat[i][j] == global_mat[i][j]) tmp++;
            }
        }
    bool check = 0;
    if (tmp == (rows*cols)) check = 1;
    ASSERT_EQ(check, 1);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix_17x17) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 17;
    int cols = 17;
    double alpha = 1.5;
    int beta = 1;
    Matrix global_mat(rows, std::vector<int>(cols));
    Matrix local_mat(rows, std::vector<int>(cols));
    global_mat = getRandomMatrix(rows, cols);
    if (procRank == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                local_mat[i][j] = global_mat[i][j];
                local_mat[i][j] = getSequentialContrast(local_mat, i, j, alpha, beta);
            }
        }
    }
    global_mat = getParallelContrast(global_mat, rows, cols, alpha, beta);
    if (procRank == 0) {
    int tmp = 0;
        for (int  i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (local_mat[i][j] == global_mat[i][j]) tmp++;
            }
        }
    bool check = 0;
    if (tmp == (rows*cols)) check = 1;
    ASSERT_EQ(check, 1);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix_23x45) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 23;
    int cols = 45;
    double alpha = 1.5;
    int beta = 1;
    Matrix global_mat(rows, std::vector<int>(cols));
    Matrix local_mat(rows, std::vector<int>(cols));
    global_mat = getRandomMatrix(rows, cols);
    if (procRank == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                local_mat[i][j] = global_mat[i][j];
                local_mat[i][j] = getSequentialContrast(local_mat, i, j, alpha, beta);
            }
        }
    }
    global_mat = getParallelContrast(global_mat, rows, cols, alpha, beta);
    if (procRank == 0) {
    int tmp = 0;
        for (int  i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (local_mat[i][j] == global_mat[i][j]) tmp++;
            }
        }
    bool check = 0;
    if (tmp == (rows*cols)) check = 1;
    ASSERT_EQ(check, 1);
    }
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
