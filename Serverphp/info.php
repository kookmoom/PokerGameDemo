<?php
$con = mysql_connect("localhost","root","901214");
if (!$con)
{
die('could not' . mysql_error());
}
else
{
mysql_select_db("poker",$con) or die(mysql_error());

$results = mysql_query("select * from Scores");
$num = 0;
while($row = mysql_fetch_array($results))
{
	$num += 1;
}
echo $num;
}
?>
