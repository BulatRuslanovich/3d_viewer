#include <gtest/gtest.h>

#include <iostream>

#include "../controller/controller.h"

class ViewerTest : public ::testing::Test {
 protected:
  s21::Model model;
  s21::Controller controller{};
  static constexpr double eps = 1e-6;

  void SetUp() override { controller = s21::Controller(&model); }
};

TEST_F(ViewerTest, CorrectCube) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.getData().clearData();
  controller.setCenter(&controller.getData());
  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, CorrectCar) {
  std::string filePath = "tests/obj/correct/car.obj";
  controller.setCenter(&controller.getData());
  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, CorrectNegativeCube) {
  std::string filePath = "../src/tests/obj/correct/cube_neg.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, IncorrectFileName) {
  std::string filePath = "../src/tests/obj/correct/abrakadabra.obj";
  controller.setCenter(&controller.getData());

  EXPECT_FALSE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, IncorrectFileExtention) {
  std::string filePath = "../src/tests/obj/correct/cube.org";
  controller.setCenter(&controller.getData());

  EXPECT_FALSE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, IncorrectFilePath) {
  std::string filePath = "../src/tests/obj/cor/cube.org";
  controller.setCenter(&controller.getData());

  EXPECT_FALSE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, EmptyFilePath) {
  std::string filePath;
  controller.setCenter(&controller.getData());

  EXPECT_FALSE(model.processObjFile(filePath));
}

/// All incorrect files

TEST_F(ViewerTest, alot_coordinates_in_vertex) {
  std::string filePath =
      "../src/tests/obj/incorrect/alot_coordinates_in_vertex.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, dot_error) {
  std::string filePath = "../src/tests/obj/incorrect/dot_error.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, facet_that_less_than_1) {
  std::string filePath =
      "../src/tests/obj/incorrect/facet_that_less_than_1.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, facet_that_not_exist) {
  std::string filePath = "../src/tests/obj/incorrect/facet_that_not_exist.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, first_minus) {
  std::string filePath = "../src/tests/obj/incorrect/first_minus.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, incorrect_notation) {
  std::string filePath = "../src/tests/obj/incorrect/incorrect_notation.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, incorrect_number) {
  std::string filePath = "../src/tests/obj/incorrect/incorrect_number.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, invalid_pretoken) {
  std::string filePath = "../src/tests/obj/incorrect/invalid_pretoken.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, invalid_token) {
  std::string filePath = "../src/tests/obj/incorrect/invalid_token.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, more_than_1_dot_in_number) {
  std::string filePath =
      "../src/tests/obj/incorrect/more_than_1_dot_in_number.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, stash) {
  std::string filePath = "../src/tests/obj/incorrect/stash.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, stash_in_line) {
  std::string filePath = "../src/tests/obj/incorrect/stash_in_line.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, test_with_russian_symb) {
  std::string filePath =
      "../src/tests/obj/incorrect/test_with_russian_symb.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, tsar_test) {
  std::string filePath = "../src/tests/obj/incorrect/tsar_test.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, vertex_less_than_3) {
  std::string filePath = "../src/tests/obj/incorrect/vertex_less_than_3.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

TEST_F(ViewerTest, zero_vertex) {
  std::string filePath = "../src/tests/obj/incorrect/zero_vertex.obj";
  controller.setCenter(&controller.getData());

  EXPECT_TRUE(model.processObjFile(filePath));
}

// TEST AFFINE

TEST_F(ViewerTest, MovePlusX) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";

  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(), 3);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_EQ(modelBefore[i].x + 3, modelAfter[i].x);
  }
}

TEST_F(ViewerTest, MoveMinusX) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";

  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    -3);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_EQ(modelBefore[i].x - 3, modelAfter[i].x);
  }
}

TEST_F(ViewerTest, MovePlusY) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(), 3);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_EQ(modelBefore[i].y + 3, modelAfter[i].y);
  }
}

TEST_F(ViewerTest, MoveMinusY) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    -3);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_EQ(modelBefore[i].y - 3, modelAfter[i].y);
  }
}

TEST_F(ViewerTest, MovePlusZ) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(), 3);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_EQ(modelBefore[i].z + 3, modelAfter[i].z);
  }
}

TEST_F(ViewerTest, MoveMinusZ) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    -3);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_EQ(modelBefore[i].z - 3, modelAfter[i].z);
  }
}

TEST_F(ViewerTest, RotateX) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    180);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, -modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, -modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, RotateY) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    180);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, -modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, -modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, RotateZ) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    180);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, -modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, -modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, SummaryXYZMirrorRotateTest) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    30);
  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    30);
  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    30);

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    -30);
  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    -30);
  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    -30);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, SummaryXRotateTest) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    30);

  controller.affine(s21::Strategy::SelectionStrategy::ROTATE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    -30);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, PlusSizeTest) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ZOOM,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    1.1);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x * 1.1, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y * 1.1, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z * 1.1, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, MinusSizeTest) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  model.processObjFile(filePath);

  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::ZOOM,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    0.9);

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x * 0.9, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y * 0.9, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z * 0.9, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, SetCenterTest) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  controller.parseFile(filePath);

  controller.setCenter(&controller.getData());
  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    20);
  controller.setCenter(&controller.getData());

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, SetCenterAfterMovingZYTest) {
  std::string filePath = "../src/tests/obj/correct/cube.obj";
  controller.parseFile(filePath);

  controller.setCenter(&controller.getData());
  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    -10);
  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    -10);
  controller.setCenter(&controller.getData());

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, SetCenterAfterMovingTest) {
  std::string filePath = "../src/tests/obj/correct/bison_pose.obj";
  controller.parseFile(filePath);

  controller.setCenter(&controller.getData());
  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    -10);
  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    -10);
  controller.setCenter(&controller.getData());

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}

TEST_F(ViewerTest, SetCenterAfterZMovingTest) {
  std::string filePath = "../src/tests/obj/correct/katana.obj";
  controller.parseFile(filePath);

  controller.setCenter(&controller.getData());
  const auto modelBefore = controller.getData().getCoordinates();

  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::X, &controller.getData(),
                    -10);
  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Y, &controller.getData(),
                    -10);
  controller.affine(s21::Strategy::SelectionStrategy::MOVE,
                    s21::Strategy::TypeCoordinate::Z, &controller.getData(),
                    10);
  controller.setCenter(&controller.getData());

  const auto modelAfter = controller.getData().getCoordinates();

  for (size_t i = 0; i < modelBefore.size(); i++) {
    EXPECT_NEAR(modelBefore[i].x, modelAfter[i].x, eps);
    EXPECT_NEAR(modelBefore[i].y, modelAfter[i].y, eps);
    EXPECT_NEAR(modelBefore[i].z, modelAfter[i].z, eps);
  }
}
