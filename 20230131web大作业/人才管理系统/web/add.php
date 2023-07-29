<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>员工信息管理系统</title>
	<style>
		input{
			margin-left: 5px;
		}
	</style>
</head>
<body>
	<?php
		// 引入数据库链接文件
		include 'conn.php';
		// 判断表单是否提交
		if ($_POST) {
			// 接收表单参数
			$name = $_POST['name'];
			$sex = $_POST['sex'];
			$birthday = $_POST['birthday'];
			$phone = $_POST['phone'];
			$address = $_POST['address'];
			$department = $_POST['department'];
			// 组装插入数据库sql语句
			$sql = "INSERT INTO employee ( name, sex, birthday, phone, address, department) VALUES ('{$name}', '{$sex}', '{$birthday}', '{$phone}', '{$address}', '{$department}')";
			// 执行sql
			$row = $pdo->exec($sql);
			// 判断是否成功！
			if ($row) {
				echo "<script>alert('添加成功！');window.location.href='index.php'</script>";
			} else {
				echo "<script>alert('添加失败！');window.location.href='add.php'</script>";
			}
		}
	?>
	<h1 align="center">添加员工信息</h1>
	<form action="add.php" method="post">
		<table width="330" align="center" border="0" style="border: 2px solid #333;padding-top: 20px;" cellspacing="0" cellpadding="10">
			<tr>
				<td align="right">员工姓名</td>
				<td>
					<input type="text" name="name" required="required">
				</td>
			</tr>
			<tr>
				<td align="right">员工姓别</td>
				<td>
					<input name="sex" type="radio" value="男" checked="checked" />男 
					<input name="sex" type="radio" value="女" />女
				</td>
			</tr>
			<tr>
				<td align="right">出生年月</td>
				<td>
					<input type="text" name="birthday" required="required">
				</td>
			</tr>
			<tr>
				<td align="right">手机号码</td>
				<td>
					<input type="text" name="phone" required="required">
				</td>
			</tr>
			<tr>
				<td align="right">家庭住址</td>
				<td>
					<input type="text" name="address" required="required">
				</td>
			</tr>
			<tr>
				<td align="right">所在部门</td>
				<td>
					<input type="text" name="department" required="required">
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<button type="submit">提    交</button>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
