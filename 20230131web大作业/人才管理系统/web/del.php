<?php 
// 引入数据库连接文件
include 'conn.php';
// 接收需要删除的数据的id
$id = $_GET['id'];
// 组装删除sql语句
$sql = "DELETE FROM employee WHERE id=$id";
// 执行删除
$row = $pdo->exec($sql);
if ($row) {
	echo "<script>alert('删除成功！');window.location.href='index.php'</script>";
} else {
	echo "<script>alert('删除失败！');window.location.href='index.php'</script>";
}

?>