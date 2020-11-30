// Copyright 2020 Zoreev Mikhail
#include "../../../modules/task_3/zoreev_m_moore_algorithm/moore_algorithm.h"

void randomCompleteGraph(size_t size, int64_t *graph) {
    std::mt19937 generator;
    generator.seed(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            graph[i * size + j] = generator() % 10 + 1;
        }
    }
    for (size_t i = 0; i < size; i++) {
        graph[i * size + i] = INT64_MIN;
    }
}

void printGraph(size_t size, int64_t *graph) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < i; j++) {
            std::cout << std::setw(2) << graph[i * size + j] << ' ';
        }
        std::cout << std::setw(2) << 'x' << ' ';
        for (size_t j = i + 1; j < size; j++) {
            std::cout << std::setw(2) << graph[i * size + j] << ' ';
        }
        std::cout << std::endl;
    }
}

void printPredecessor(size_t size, uint64_t *predecessor) {
    for (size_t i = 0; i < size; i++) {
        std::cout << std::setw(2) << predecessor[i] << ' ';
    }
    std::cout << std::endl;
}

size_t *mooreAlgorithm(size_t size, int64_t *graph, size_t root) {
    if (size < 2) {
        throw std::runtime_error("WRONG SIZE");
    }
    int64_t *distance = new int64_t[size];
    uint64_t *predecessor = new size_t[size];
    for (size_t i = 0; i < size; i++) {
        distance[i] = INT32_MAX;
        predecessor[i] = SIZE_MAX;
    }
    distance[root] = 0;
    predecessor[root] = root;

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < j; k++) {
                if ((graph[j * size + k] != INT64_MIN) && (distance[k] > distance[j] + graph[j * size + k])) {
                    distance[k] = distance[j] + graph[j * size + k];
                    predecessor[k] = j;
                }
            }
            for (size_t k = j + 1; k < size; k++) {
                if ((graph[j * size + k] != INT64_MIN) && (distance[k] > distance[j] + graph[j * size + k])) {
                    distance[k] = distance[j] + graph[j * size + k];
                    predecessor[k] = j;
                }
            }
        }
    }
    delete[] distance;

    return predecessor;
}

uint64_t *mooreAlgorithmParallel(uint64_t size, int64_t *graph, size_t root) {
    int rank, process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        throw std::runtime_error("WRONG SIZE");
    }
    int64_t *distance = new int64_t[size];
    uint64_t *predecessor = new size_t[size];
    int64_t *distance_buffer = new int64_t[size * process_count];
    uint64_t *predecessor_buffer = new size_t[size * process_count];
    for (size_t i = 0; i < size; i++) {
        distance[i] = INT32_MAX;
        predecessor[i] = SIZE_MAX;
    }
    distance[root] = 0;
    predecessor[root] = root;

    size_t part = size / static_cast<size_t>(process_count);
    size_t start = rank * part, end = (rank + 1) * part;
    if (rank == process_count - 1) {
        end = size;
    }
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = start; j < end; j++) {
            for (size_t k = 0; k < j; k++) {
                if ((graph[j * size + k] != INT64_MIN) && (distance[k] > distance[j] + graph[j * size + k])) {
                    distance[k] = distance[j] + graph[j * size + k];
                    predecessor[k] = j;
                }
            }
            for (size_t k = j + 1; k < size; k++) {
                if ((graph[j * size + k] != INT64_MIN) && (distance[k] > distance[j] + graph[j * size + k])) {
                    distance[k] = distance[j] + graph[j * size + k];
                    predecessor[k] = j;
                }
            }
        }

        MPI_Allgather(distance, size, MPI_INT64_T, distance_buffer, size, MPI_INT64_T, MPI_COMM_WORLD);
        MPI_Allgather(predecessor, size, MPI_UINT64_T, predecessor_buffer, size, MPI_UINT64_T, MPI_COMM_WORLD);
        for (size_t k = 0; k < size; k++) {
            for (size_t j = 0; j < process_count; j++) {
                if (distance_buffer[j * size + k] < distance[k]) {
                    distance[k] = distance_buffer[j * size + k];
                    predecessor[k] = predecessor_buffer[j * size + k];
                }
            }
        }
    }
    delete[] distance;
    delete[] distance_buffer;
    delete[] predecessor_buffer;

    return predecessor;
}
