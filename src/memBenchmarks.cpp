//
// Created by gonciarz on 4/24/18.
//

#include <gtest/gtest.h>
#undef APR_BENCHMARK
#include "misc/APRTimer.hpp"
#include "memBenchmarks.h"
#include "TestTools.hpp"

namespace {
    const int xSize = 64 * 32 * 24 * 4;
    const int ySize = 1024;

    TEST(MemBenchmarTest, COPY1D) {
        APRTimer timer(true);
        using ImgType = float ;

        MeshData<ImgType> input = getRandInitializedMesh<ImgType>(xSize,ySize,1,1,true);
        std::cout << input << std::endl;

        MeshData<ImgType> result(input, false /* don't copy */);

        timer.start_timer("GpuTimeWithMemTransfer");
        memCopy1D(input, result);
        timer.stop_timer();

        if (false) {
            input.printMesh(3, 1);
            result.printMesh(3, 1);
        }
        EXPECT_EQ(compareMeshes(input, result, 0.01), 0);
    }

    TEST(MemBenchmarTest, COPY2D) {
        APRTimer timer(true);
        using ImgType = float ;

        MeshData<ImgType> input = getRandInitializedMesh<ImgType>(xSize,ySize,1,1,true);
        std::cout << input << std::endl;

        MeshData<ImgType> result(input, false /* don't copy */);

        timer.start_timer("GpuTimeWithMemTransfer");
        memCopy2D(input, result);
        timer.stop_timer();

        if (false) {
            input.printMesh(3, 1);
            result.printMesh(3, 1);
        }
        EXPECT_EQ(compareMeshes(input, result, 0.01), 0);
    }

    TEST(MemBenchmarTest, CONV2D) {
        APRTimer timer(true);
        using ImgType = float ;

        MeshData<ImgType> input = getRandInitializedMesh<ImgType>(16*1024*4,16*1024*2,1,1,true);
        std::cout << input << std::endl;

        MeshData<ImgType> result(input, false /* don't copy */);

        MeshData<ImgType> kernel(3,3,1,0);
        kernel.at(2,1,0) = 1;
        kernel.at(0,1,0) = 1;
        kernel.at(1,2,0) = 1;

        timer.start_timer("GpuTimeWithMemTransfer");
        conv2d(input, result, kernel);
        timer.stop_timer();

        if (false) {
            input.printMeshT(3, 1);
            result.printMeshT(3, 1);
        }
//        EXPECT_EQ(compareMeshes(input, result, 0.01), 0);
    }

    TEST(MemBenchmarTest, CONV3D) {
        APRTimer timer(true);
        using ImgType = float ;

        MeshData<ImgType> input = getRandInitializedMesh<ImgType>(1024,1024,1024,1,true);
        std::cout << input << std::endl;

        MeshData<ImgType> result(input, false /* don't copy */);

        MeshData<ImgType> kernel(3,3,1,1);

        timer.start_timer("GpuTimeWithMemTransfer");
        conv3d(input, result, kernel);
        timer.stop_timer();

        if (false) {
            input.printMeshT(4, 0);
            result.printMeshT(4, 0);
        }
        EXPECT_EQ(compareMeshes(input, result, 0.01), 0);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
