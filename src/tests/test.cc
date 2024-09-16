#include <gtest/gtest.h>

#include <iostream>

#include "../model/obj.h"

TEST(ObjTest, ConstructorNoParams) {
  s21::obj *empty_object = s21::obj::getInstance();
  EXPECT_EQ(empty_object->get_vertices(), 0);
  EXPECT_EQ(empty_object->get_polygons(), 0);
  EXPECT_EQ(empty_object->get_minX(), 0);
  EXPECT_EQ(empty_object->get_maxX(), 0);
  EXPECT_EQ(empty_object->get_minY(), 0);
  EXPECT_EQ(empty_object->get_maxY(), 0);
  EXPECT_EQ(empty_object->get_minZ(), 0);
  EXPECT_EQ(empty_object->get_maxZ(), 0);
  delete empty_object;
}

TEST(ObjTest, ConstructorThrowNullFile) {
  s21::obj *object_throw = s21::obj::getInstance();
  EXPECT_THROW(object_throw->parser("obj.obj"), std::invalid_argument);
  delete object_throw;
}

TEST(ObjTest, ConstructorThrowTxtFile) {
  s21::obj *object_throw = s21::obj::getInstance();
  EXPECT_THROW(object_throw->parser("../src/obj/cube.txt"),
               std::invalid_argument);
  delete object_throw;
}

TEST(ObjTest, ConstructorCube) {
  s21::obj *object_cube = s21::obj::getInstance();
  int vertices_rows = 8, polygons_rows = 12;
  object_cube->parser("../src/obj/cube.obj");
  double matrix_vertices[8][3]{{-1.5, -1.5, -1.5}, {-1.5, 1.5, -1.5},
                               {1.5, 1.5, -1.5},   {1.5, -1.5, -1.5},
                               {-1.5, -1.5, 1.5},  {-1.5, 1.5, 1.5},
                               {1.5, 1.5, 1.5},    {1.5, -1.5, 1.5}};
  int matrix_polygons[12][3]{{3, 7, 8}, {3, 8, 4}, {1, 5, 6}, {1, 6, 2},
                             {7, 3, 2}, {7, 2, 6}, {4, 8, 5}, {4, 5, 1},
                             {8, 7, 6}, {8, 6, 5}, {3, 4, 1}, {3, 1, 2}};

  EXPECT_EQ(object_cube->get_vertices(), vertices_rows);
  EXPECT_EQ(object_cube->get_polygons(), polygons_rows);
  EXPECT_EQ(object_cube->get_minX(), 0.0);
  EXPECT_EQ(object_cube->get_maxX(), 1.0);
  EXPECT_EQ(object_cube->get_minY(), 0.0);
  EXPECT_EQ(object_cube->get_maxY(), 1.0);
  EXPECT_EQ(object_cube->get_minZ(), 0.0);
  EXPECT_EQ(object_cube->get_maxZ(), 1.0);

  for (int i = 0; i < object_cube->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(object_cube->get_vertices(i, j), matrix_vertices[i][j]);
    }
  }

  for (int i = 0; i < object_cube->get_polygons_rows(); i++) {
    for (int j = 0; j < object_cube->get_polygons_cols(); j++) {
      EXPECT_EQ(object_cube->get_polygons(i, j), matrix_polygons[i][j]);
    }
  }

  for (int i = 0; i < object_cube->get_polygons(); i++) {
    EXPECT_EQ(object_cube->get_vertices(i), 3);
  }
  delete object_cube;
}

TEST(ObjTest, AfinZoomTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double zoom_matrix[3][3] = {0};
  zoom_matrix[2][0] = 10.0;
  object->affine_transform(zoom_matrix);
  double ans_matrix[8][3]{{-15.0, -15.0, -15.0}, {-15.0, 15.0, -15.0},
                          {15.0, 15.0, -15.0},   {15.0, -15.0, -15.0},
                          {-15.0, -15.0, 15.0},  {-15.0, 15.0, 15.0},
                          {15.0, 15.0, 15.0},    {15.0, -15.0, 15.0}};
  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

TEST(ObjTest, AfinShiftXTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double shift_matrix[3][3] = {0};
  shift_matrix[0][0] = 10.0;
  object->affine_transform(shift_matrix);
  double ans_matrix[8][3]{{8.5, -1.5, -1.5}, {8.5, 1.5, -1.5},
                          {11.5, 1.5, -1.5}, {11.5, -1.5, -1.5},
                          {8.5, -1.5, 1.5},  {8.5, 1.5, 1.5},
                          {11.5, 1.5, 1.5},  {11.5, -1.5, 1.5}};

  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

TEST(ObjTest, AfinShiftYTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double shift_matrix[3][3] = {0};
  shift_matrix[0][1] = 10.0;
  object->affine_transform(shift_matrix);
  double ans_matrix[8][3]{{-1.5, 8.5, -1.5}, {-1.5, 11.5, -1.5},
                          {1.5, 11.5, -1.5}, {1.5, 8.5, -1.5},
                          {-1.5, 8.5, 1.5},  {-1.5, 11.5, 1.5},
                          {1.5, 11.5, 1.5},  {1.5, 8.5, 1.5}};

  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

TEST(ObjTest, AfinShiftZTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double shift_matrix[3][3] = {0};
  shift_matrix[0][2] = 10.0;
  object->affine_transform(shift_matrix);
  double ans_matrix[8][3]{{-1.5, -1.5, 8.5},  {-1.5, 1.5, 8.5},
                          {1.5, 1.5, 8.5},    {1.5, -1.5, 8.5},
                          {-1.5, -1.5, 11.5}, {-1.5, 1.5, 11.5},
                          {1.5, 1.5, 11.5},   {1.5, -1.5, 11.5}};
  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

TEST(ObjTest, AfinRotateXTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double rotate_matrix[3][3] = {0};
  rotate_matrix[1][0] = 10.0;
  object->affine_transform(rotate_matrix);
  double ans_matrix[8][3]{
      {-1.5, 0.44257563, 2.074639},  {-1.5, -2.074639, 0.44257563},
      {1.5, -2.074639, 0.44257563},  {1.5, 0.44257563, 2.074639},
      {-1.5, 2.074639, -0.44257563}, {-1.5, -0.44257563, -2.074639},
      {1.5, -0.44257563, -2.074639}, {1.5, 2.074639, -0.44257563}};

  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

TEST(ObjTest, AfinRotateYTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double rotate_matrix[3][3] = {0};
  rotate_matrix[1][1] = 10.0;
  object->affine_transform(rotate_matrix);
  double ans_matrix[8][3]{
      {2.074639, -1.5, 0.44257563},  {2.074639, 1.5, 0.44257563},
      {-0.44257563, 1.5, 2.074639},  {-0.44257563, -1.5, 2.074639},
      {0.44257563, -1.5, -2.074639}, {0.44257563, 1.5, -2.074639},
      {-2.074639, 1.5, -0.44257563}, {-2.074639, -1.5, -0.44257563}};
  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

TEST(ObjTest, AfinRotateZTen) {
  s21::obj *object = s21::obj::getInstance();
  object->parser("../src/obj/cube.obj");
  double rotate_matrix[3][3] = {0};
  rotate_matrix[1][2] = 10.0;
  object->affine_transform(rotate_matrix);
  double ans_matrix[8][3]{
      {0.44257563, 2.074639, -1.5},   {2.074639, -0.44257563, -1.5},
      {-0.44257563, -2.074639, -1.5}, {-2.074639, 0.44257563, -1.5},
      {0.44257563, 2.074639, 1.5},    {2.074639, -0.44257563, 1.5},
      {-0.44257563, -2.074639, 1.5},  {-2.074639, 0.44257563, 1.5}};
  for (int i = 0; i < object->get_vertices(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(object->get_vertices(i, j), ans_matrix[i][j]);
    }
  }
  delete object;
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}