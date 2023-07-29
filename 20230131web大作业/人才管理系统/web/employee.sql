/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 50553
 Source Host           : localhost:3306
 Source Schema         : employee

 Target Server Type    : MySQL
 Target Server Version : 50553
 File Encoding         : 65001

 Date: 30/01/2023 19:09:31
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for admin
-- ----------------------------
DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account` varchar(100) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of admin
-- ----------------------------
INSERT INTO `admin` VALUES (1, 'admin', '123456');
INSERT INTO `admin` VALUES (2, 'school', '123456');

-- ----------------------------
-- Table structure for employee
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `sex` varchar(2) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `birthday` varchar(100) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `phone` varchar(20) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `address` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `department` varchar(100) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 15 CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of employee
-- ----------------------------
INSERT INTO `employee` VALUES (1, '樊梨花', '女', '1997-12-25', '13845221265', '湖北省武汉市中环路23号', '销售部');
INSERT INTO `employee` VALUES (2, '薛丁山', '男', '1994-08-30', '13341451875', '北京市朝阳区新五路48号', '研发部');
INSERT INTO `employee` VALUES (3, '秦叔宝', '男', '1965-02-13', '13574896541', '安徽省合肥市中山路12号', '人事部');
INSERT INTO `employee` VALUES (4, '薛仁贵', '男', '1921-01-25', '13348746521', '河北省石家庄市鹿泉区新庄路98号', '销售部');
INSERT INTO `employee` VALUES (5, '铁世文', '男', '1954-03-14', '13978661298', '浙江省江苏市通州区上海路14号', '市场部');
INSERT INTO `employee` VALUES (6, '李世民', '男', '1935-01-11', '13245563465', '海南省海滨区桶珠路34号', '市场部');
INSERT INTO `employee` VALUES (7, '秦香莲', '女', '1935-01-11', '13792883542', '天津市河海区北海路74号', '人事部');
INSERT INTO `employee` VALUES (8, '李鹤鸣', '女', '1994-10-25', '13645385422', '甘肃省兰州市安宁区东路967号', '研发部');
INSERT INTO `employee` VALUES (12, '李刚', '男', '1997-12-25', '13348746521', '上海市浦东新区新华路123号', '销售部');

-- ----------------------------
-- Table structure for program
-- ----------------------------
DROP TABLE IF EXISTS `program`;
CREATE TABLE `program`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '主键',
  `title` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '项目名称',
  `type` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '项目类型',
  `content` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '项目内容',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 9 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '项目信息' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of program
-- ----------------------------
INSERT INTO `program` VALUES (2, '1', '18888', '1');
INSERT INTO `program` VALUES (6, '3', '3', '3');
INSERT INTO `program` VALUES (5, '1', '2', '3');
INSERT INTO `program` VALUES (8, '8888', '533', '5333');


SET FOREIGN_KEY_CHECKS = 1;
