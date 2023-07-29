<?php
// 开启session·
session_start();
// 检测登录是否登录
if (!isset($_SESSION["account"])) {
    echo "<script>alert('请登录')</script>";
    header('Location: login.php');
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>员工信息管理系统</title>
</head>
<body>
	<h1 align="center">所有员工信息</h1>
	<p align="center"><span>欢迎 <strong><?php echo $_SESSION['account']; ?></strong> 登录！</span>
	|  <a href="logout.php">退出登录</a> 
	 |&nbsp;&nbsp; <span><a href="add.php">添加员工信息</a></span>
	 
	  |&nbsp;&nbsp; <span><a href="program_List.php">项目信息管理</a></span>
	 
	 	  |&nbsp;&nbsp; <span><a href="programadd.php">添加项目信息</a></span>
	 </p>
	<p align="center">
		<form action="" method="get" style="text-align: center;">
			<input type="text" placeholder="请输入要查询的姓名" name="keyword">&nbsp;&nbsp;
			<input type="submit" value="查询">
		</form>
	</p>
	<table width="1000" align="center" border="1" cellspacing="0" cellpadding="5">
		<tr>
			<th>ID</th>
			<th>姓名</th>
			<th>性别</th>
			<th>出生年月</th>
			<th>手机号码</th>
			<th>家庭住址</th>
			<th>所在部门</th>
			<th>操作</th>
		</tr>
		<?php
			// 引入数据库连接文件
			include 'conn.php';
			// sql查询语句
			$sql = "select * from employee where 1 = 1";
			// 如果查询框存在查询条件，则拼接查询条件
			if ($_GET['keyword']) {
				$sql .= " AND name like '%{$_GET['keyword']}%'";
			}
			// 执行查询语句
			// query执行一条SQL语句，如果通过，则返回一个PDOStatement对象,可以直接遍历这个返回的记录集 (query用于select)
	        $state = $pdo->query($sql); 
			//获取结果集中的所有数据
	        $res = $state->fetchAll(PDO::FETCH_ASSOC);
	        if (empty($res)) {
	        	echo "<tr>";
	        	echo "<td colspan='8' align='center'>
	        	没有姓名为"."<span style='color:red;font-weight:blod;'> ".$_GET['keyword']." </span>"."<span>的员工
	        	</td>";
	        	echo "</tr>";
	        }
                
	        // 将结果集循环遍历显示在表格中
	        foreach ($res as $key => $value) {
		?>
		<tr align="center">
			<td><?php echo $value['id']; ?></td>
			<td><?php echo $value['name']; ?></td>
			<td><?php echo $value['sex']; ?></td>
			<td><?php echo $value['birthday']; ?></td>
			<td><?php echo $value['phone']; ?></td>
			<td><?php echo $value['address']; ?></td>
			<td><?php echo $value['department']; ?></td>
			<td>
				<a href="edit.php?id=<?php echo $value['id']; ?>">编辑</a>
				<a onclick="return confirm('您确定删除吗？');" href="del.php?id=<?php echo $value['id']; ?>">删除</a>
			</td>
		</tr>
		<?php
			// 循环结束符
			}
		?>
	</table>
</body>
</html>