<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>注册</title>
</head>
<body>
	<?php
		//引入数据库连接文件 
		include 'conn.php';
		// 当提交登录表单后
		if ($_POST) {
			// 接收用户账号
			$account = $_POST['account'];
			// 接收用户密码
			$password = $_POST['password'];
			// 接收用户确认密码
			$repassword = $_POST['repassword'];
			if ($password != $repassword) {
				echo "<script>alert('两次输入的密码不一致！');window.location.href='register.php'</script>";
			}
			// 组装插入数据库sql语句
			$sql = "INSERT INTO admin ( account, password) VALUES ('{$account}', '{$password}')";
			// 执行sql
			$row = $pdo->exec($sql);
			// 判断是否成功！
			if ($row) {
				echo "<script>alert('注册成功！请登录');window.location.href='login.php'</script>";
			} else {
				echo "<script>alert('注册失败！');window.location.href='register.php'</script>";
			}
		}
	?>
    
	<h1 align="center">员工管理系统注册</h1>
	<form action="register.php" method="post">
		<table width="300" align="center" border="0" style="border: 2px solid #333;padding-top: 15px;" cellspacing="0" cellpadding="10">
			<tr>
				<td align="right">账号</td>
				<td>
					<input type="text" name="account" required="required">
				</td>
			</tr>
			<tr>
				<td align="right">密码</td>
				<td>
					<input type="text" name="password" required="required">
				</td>
			</tr>
			<tr>
				<td align="right">确认密码</td>
				<td>
					<input type="text" name="repassword" required="required">
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<button type="submit">注   册</button>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>