<html><body><h1>It works!</h1></body></html>

<?php
	if (isset($_GET["password"]))
	{
		echo"good";
	}
	else
	{
		echo"bad";
	}
$con = mysql_connect("localhost","root","901214");
if (!$con)
{
die('could not' . mysql_error());
}
else
{
echo"connect!\n";

mysql_select_db("poker",$con) or die(mysql_error());
$score =(int) $_GET["password"];

$results = mysql_query("insert into Scores (Scor,Name) values($score,'kook')");
$num = 0;
while($row = mysql_fetch_array($results))
{
	$num += 1;
	echo $row['Name'];
}
echo $num;
}
?>
