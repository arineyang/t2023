<?php 
// 开启session
session_start();
// 清空session
$_SESSION = array();
// 删除session文件
session_destroy();
// 退出登录跳转到登录页面
header('Location: login.php');
 ?>
