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
		// 判断如果存在通过get方式传过来id说明，需要修改，则查询数据
		if (!empty($_GET['id'])) {
			// 接收需要修改的数据的id
			$id = $_GET['id'];
			// 根据id查询出当前需要修改的数据
			// 组装sql语句
			$sql = "select * from employee where id = {$id}";
			// 执行查询
			$state = $pdo->query($sql); 
			// 获取结果集中的数据,将其显示在表单中
	        $result = $state->fetch(PDO::FETCH_ASSOC);
		}
		


		// 判断修改表单是否提交
		if ($_POST) {
			// 接收表单参数
			$id = $_POST['id'];
			$name = $_POST['name'];
			$sex = $_POST['sex'];
			$birthday = $_POST['birthday'];
			$phone = $_POST['phone'];
			$address = $_POST['address'];
			$department = $_POST['department'];
			// 组装更新sql语句
			$sql = "UPDATE employee SET name='{$name}', sex='{$sex}', birthday='{$birthday}', phone='{$phone}', address='{$address}', department='{$department}'  WHERE id=$id";
			// 执行sql
			$row = $pdo->exec($sql);
			// 判断是否成功！
			if ($row) {
				echo "<script>alert('修改成功！');window.location.href='index.php'</script>";
			} else {
				echo "<script>alert('修改失败！');window.location.href='edit.php'</script>";
			}
		}
	?>
	<h1 align="center">修改员工信息</h1>
	<form action="edit.php" method="post">
		<table width="330" align="center" border="0" style="border: 2px solid #333;" cellspacing="0" cellpadding="10">
			<tr>
				<td align="right">员工姓名</td>
				<td>
					<input type="text" name="name" value="<?php echo $result['name']; ?>">
				</td>
			</tr>
			<tr>
				<td align="right">员工姓别</td>
				<td>
					<input name="sex" type="radio" value="男" <?php if ($result['sex'] == '男') { echo "checked='checked'"; } ?> />男 
					<input name="sex" type="radio" value="女" <?php if ($result['sex'] == '女') { echo "checked='checked'"; } ?> />女
				</td>
			</tr>
			<tr>
				<td align="right">出生年月</td>
				<td>
					<input type="text" name="birthday" value="<?php echo $result['birthday']; ?>">
				</td>
			</tr>
                        
			<tr>
				<td align="right">手机号码</td>
				<td>
					<input type="text" name="phone" value="<?php echo $result['phone']; ?>">
				</td>
			</tr>
			<tr>
				<td align="right">家庭住址</td>
				<td>
					<input type="text" name="address" value="<?php echo $result['address']; ?>">
				</td>
			</tr>
			<tr>
				<td align="right">所在部门</td>
				<td>
					<input type="text" name="department" value="<?php echo $result['department']; ?>">
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<input type="hidden" name="id" value="<?php echo $result['id']; ?>">
					<button type="submit">修    改</button>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>