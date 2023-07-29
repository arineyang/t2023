<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>登录</title>
</head>
<body>
	<?php
		// 开启session·
		session_start();
		//引入数据库连接文件 
		include 'conn.php';
		// 当提交登录表单后
		if ($_POST) {
			// 接收用户账号
			$account = $_POST['account'];
			// 接收用户密码
			$password = $_POST['password'];
			// sql查询语句
			$sql = "select * from admin where account = '{$account}' and password = '{$password}'";
			// 执行查询，验证登录
			$state = $pdo->query($sql); 
			// 获取结果集中的数据,将其显示在表单中
	        $row = $state->fetch(PDO::FETCH_ASSOC);
	        // 如果当前用户名和密码在数据库中存在，则表示登录成功，否则失败！
	        if ($row) {
	        	// 登录成功，将用户账号存入session中
	        	$_SESSION['account'] = $row['account'];
				echo "<script>alert('登录成功！');window.location.href='index.php'</script>";
			} else {
				echo "<script>alert('登录失败！');window.location.href='login.php'</script>";
			}
		}
	?>
	<h1 align="center">员工管理系统登录</h1>
	<form action="login.php" method="post">
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
				<td colspan="2" align="center">
					<button type="submit">登   录</button>
				</td>
			</tr>
		</table>
	</form>
</body>

</html>