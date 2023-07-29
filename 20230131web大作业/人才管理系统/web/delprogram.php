
<?php 
// 引入数据库连接文件
include 'conn.php';
// 接收需要删除的数据的id


header("Content-Type:text/html;charset=utf-8");
$id = $_GET['id'];
// 组装删除sql语句
$sql = "DELETE FROM program WHERE id=$id";
// 执行删除
$row = $pdo->exec($sql);
if ($row) {
	echo "<script>alert('删除成功！');window.location.href='program_List.php'</script>";
} else {
	echo "<script>alert('删除失败！');window.location.href='program_List.php'</script>";
}
?>