/*
Navicat MySQL Data Transfer

Source Server         : root
Source Server Version : 50144
Source Host           : localhost:3306
Source Database       : css

Target Server Type    : MYSQL
Target Server Version : 50144
File Encoding         : 65001

Date: 2014-08-21 16:25:45
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for attend
-- ----------------------------
DROP TABLE IF EXISTS `attend`;
CREATE TABLE `attend` (
  `aid` int(8) NOT NULL AUTO_INCREMENT,
  `aname` varchar(64) NOT NULL,
  `aloc` varchar(64) DEFAULT NULL,
  `atime` datetime DEFAULT NULL,
  `gname` varchar(32) NOT NULL,
  `arange` varchar(64) NOT NULL,
  `mark` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`aid`),
  KEY `gname` (`gname`),
  CONSTRAINT `attend_ibfk_1` FOREIGN KEY (`gname`) REFERENCES `guest` (`gname`)
) ENGINE=InnoDB AUTO_INCREMENT=10000003 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of attend
-- ----------------------------
INSERT INTO `attend` VALUES ('10000001', '上课', 'a401', '2014-08-21 15:53:24', '张三', '法学院', null);
INSERT INTO `attend` VALUES ('10000002', '早操', '操场', '2014-08-21 15:54:11', '张三', '法学院', null);

-- ----------------------------
-- Table structure for check
-- ----------------------------
DROP TABLE IF EXISTS `check`;
CREATE TABLE `check` (
  `sid` int(8) NOT NULL,
  `aid` int(8) NOT NULL,
  `cstat` varchar(16) NOT NULL DEFAULT '缺勤',
  PRIMARY KEY (`sid`,`aid`),
  KEY `aid` (`aid`),
  CONSTRAINT `check_ibfk_1` FOREIGN KEY (`sid`) REFERENCES `student` (`sid`),
  CONSTRAINT `check_ibfk_2` FOREIGN KEY (`aid`) REFERENCES `attend` (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of check
-- ----------------------------

-- ----------------------------
-- Table structure for dept
-- ----------------------------
DROP TABLE IF EXISTS `dept`;
CREATE TABLE `dept` (
  `deptno` tinyint(2) NOT NULL,
  `deptname` varchar(64) NOT NULL,
  PRIMARY KEY (`deptno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dept
-- ----------------------------
INSERT INTO `dept` VALUES ('1', '文史学院');
INSERT INTO `dept` VALUES ('2', '计算机科学与工程学院');
INSERT INTO `dept` VALUES ('3', '电气信息工程学院');
INSERT INTO `dept` VALUES ('4', '法学院');
INSERT INTO `dept` VALUES ('5', '体育学院');
INSERT INTO `dept` VALUES ('6', '教务处');
INSERT INTO `dept` VALUES ('7', '生物科学与工程学院');
INSERT INTO `dept` VALUES ('8', '医学院');
INSERT INTO `dept` VALUES ('9', '商学院');
INSERT INTO `dept` VALUES ('10', '经济学院');
INSERT INTO `dept` VALUES ('11', '管理学院');
INSERT INTO `dept` VALUES ('12', '外国语学院');
INSERT INTO `dept` VALUES ('13', '音乐舞蹈学院');
INSERT INTO `dept` VALUES ('14', '设计艺术学院');
INSERT INTO `dept` VALUES ('15', '数学与信息科学学院');
INSERT INTO `dept` VALUES ('16', '材料科学与工程学院');
INSERT INTO `dept` VALUES ('17', '化学与化学工程学院');
INSERT INTO `dept` VALUES ('18', '预科教育学院');
INSERT INTO `dept` VALUES ('19', '基础教育学院');
INSERT INTO `dept` VALUES ('20', '马克思主义学院');
INSERT INTO `dept` VALUES ('21', '土木工程学院');
INSERT INTO `dept` VALUES ('22', '机电工程学院');
INSERT INTO `dept` VALUES ('23', '阿拉伯语学院');
INSERT INTO `dept` VALUES ('24', '附属中学');
INSERT INTO `dept` VALUES ('25', '信息与计算科学学院');

-- ----------------------------
-- Table structure for guest
-- ----------------------------
DROP TABLE IF EXISTS `guest`;
CREATE TABLE `guest` (
  `gname` varchar(32) NOT NULL,
  `password` varchar(16) NOT NULL,
  `identify` varchar(16) NOT NULL DEFAULT '普通用户',
  `deptno` tinyint(2) NOT NULL,
  `mark` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`gname`),
  KEY `deptno` (`deptno`),
  CONSTRAINT `guest_ibfk_1` FOREIGN KEY (`deptno`) REFERENCES `dept` (`deptno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of guest
-- ----------------------------
INSERT INTO `guest` VALUES ('john', '123', '系统管理员', '6', null);
INSERT INTO `guest` VALUES ('张三', '123', '普通用户', '1', null);
INSERT INTO `guest` VALUES ('李四', '123', '普通用户', '2', null);
INSERT INTO `guest` VALUES ('王五', '123', '普通用户', '7', null);

-- ----------------------------
-- Table structure for major
-- ----------------------------
DROP TABLE IF EXISTS `major`;
CREATE TABLE `major` (
  `mid` smallint(4) NOT NULL AUTO_INCREMENT,
  `mname` varchar(32) NOT NULL,
  `deptno` tinyint(2) DEFAULT NULL,
  PRIMARY KEY (`mid`),
  KEY `deptno` (`deptno`),
  CONSTRAINT `major_ibfk_1` FOREIGN KEY (`deptno`) REFERENCES `dept` (`deptno`)
) ENGINE=InnoDB AUTO_INCREMENT=1053 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of major
-- ----------------------------
INSERT INTO `major` VALUES ('1001', '信息与计算科学', '25');
INSERT INTO `major` VALUES ('1002', '数学与应用数学', '25');
INSERT INTO `major` VALUES ('1003', '统计学', '25');
INSERT INTO `major` VALUES ('1004', '会计学', '9');
INSERT INTO `major` VALUES ('1005', '财务管理', '9');
INSERT INTO `major` VALUES ('1006', '工商管理', '9');
INSERT INTO `major` VALUES ('1007', '电子商务', '9');
INSERT INTO `major` VALUES ('1008', '物流管理', '9');
INSERT INTO `major` VALUES ('1009', '材料科学与工程', '16');
INSERT INTO `major` VALUES ('1010', '材料科学与工程', '16');
INSERT INTO `major` VALUES ('1011', '材料成型与控制', '16');
INSERT INTO `major` VALUES ('1012', '经济学', '10');
INSERT INTO `major` VALUES ('1013', '国际经济与贸易', '10');
INSERT INTO `major` VALUES ('1014', '金融学', '10');
INSERT INTO `major` VALUES ('1015', '汉语言文学', '1');
INSERT INTO `major` VALUES ('1016', '历史学', '1');
INSERT INTO `major` VALUES ('1017', '新闻学', '1');
INSERT INTO `major` VALUES ('1018', '传播学', '1');
INSERT INTO `major` VALUES ('1019', '广告学', '1');
INSERT INTO `major` VALUES ('1020', '行政管理系', '11');
INSERT INTO `major` VALUES ('1021', '公共事业管理系', '11');
INSERT INTO `major` VALUES ('1022', '旅游管理系', '11');
INSERT INTO `major` VALUES ('1023', '人力资源管理系', '11');
INSERT INTO `major` VALUES ('1024', '法学', '4');
INSERT INTO `major` VALUES ('1025', '英语', '12');
INSERT INTO `major` VALUES ('1026', '日语', '12');
INSERT INTO `major` VALUES ('1027', '化学工程与工艺', '17');
INSERT INTO `major` VALUES ('1028', '过程装备与控制工程', '17');
INSERT INTO `major` VALUES ('1029', '过程装备与控制工程', '17');
INSERT INTO `major` VALUES ('1030', '制药工程', '17');
INSERT INTO `major` VALUES ('1031', '计算机科学与技术', '2');
INSERT INTO `major` VALUES ('1032', '软件工程', '2');
INSERT INTO `major` VALUES ('1033', '网络工程', '2');
INSERT INTO `major` VALUES ('1034', '　信息管理与信息系统', '2');
INSERT INTO `major` VALUES ('1035', '艺术设计', '14');
INSERT INTO `major` VALUES ('1036', '绘画', '14');
INSERT INTO `major` VALUES ('1037', '动画', '14');
INSERT INTO `major` VALUES ('1038', '音乐表演', '13');
INSERT INTO `major` VALUES ('1039', '音乐学', '13');
INSERT INTO `major` VALUES ('1040', '舞蹈学', '13');
INSERT INTO `major` VALUES ('1041', '新疆民考民预科班', '18');
INSERT INTO `major` VALUES ('1042', '新疆民考民预科班', '18');
INSERT INTO `major` VALUES ('1043', '生物工程', '7');
INSERT INTO `major` VALUES ('1044', '生物技术', '7');
INSERT INTO `major` VALUES ('1045', '生物科学', '7');
INSERT INTO `major` VALUES ('1046', '通信工程', '3');
INSERT INTO `major` VALUES ('1047', '电子信息工程', '3');
INSERT INTO `major` VALUES ('1048', '自动化', '3');
INSERT INTO `major` VALUES ('1049', '信息工程', '3');
INSERT INTO `major` VALUES ('1050', '电气工程及其自动化', '3');
INSERT INTO `major` VALUES ('1051', '测控技术与仪器', '3');
INSERT INTO `major` VALUES ('1052', '土木工程', '21');

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `sid` int(8) NOT NULL AUTO_INCREMENT,
  `sname` varchar(32) NOT NULL,
  `mid` smallint(4) NOT NULL,
  `grade` smallint(4) DEFAULT NULL,
  `class` tinyint(1) DEFAULT NULL,
  `face` varchar(255) DEFAULT NULL,
  `finger` varchar(255) DEFAULT NULL,
  `mark` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`sid`),
  KEY `mid` (`mid`),
  CONSTRAINT `student_ibfk_1` FOREIGN KEY (`mid`) REFERENCES `major` (`mid`)
) ENGINE=InnoDB AUTO_INCREMENT=20113305 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('10000001', '张明', '1001', '2011', '2', null, null, null);
INSERT INTO `student` VALUES ('10000002', '王涛', '1001', '2011', '2', null, null, null);
INSERT INTO `student` VALUES ('10000003', '陈超', '1001', '2011', '2', null, null, null);
INSERT INTO `student` VALUES ('20113303', '威迪文', '1001', '2011', '2', null, null, null);
INSERT INTO `student` VALUES ('20113304', '方式', '1001', '2011', '2', null, null, null);
