<?php
	// 数据库连接参数
	//数据库主机
	$host = "127.0.0.1"; 
	// 端口
	$port = "3306";
	// 数据库用户名
	$username = "root"; 
	// 数据库密码
	$password = "root"; 
	// 数据库名称
	$dbname = "employee"; 
	// 字符编码
	$charset = "utf8"; 
	// dsn连接参数
	$dsn = "mysql:dbname=$dbname;host=$host;port=$port;charset=$charset";

	try{
		$pdo = new PDO($dsn, $username, $password);
		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);    // 设置sql语句查询如果出现问题 就会抛出异常
		// 设置数据库编码
		$pdo->exec('set names utf8'); 
	} catch(PDOException $e){
		die("连接失败: ".$e->getMessage());
	}
?>
