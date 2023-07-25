<?php
$con = new mysqli("localhost", "root", "", "news");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

$sql = "SELECT * FROM news";
$result = $con->query($sql);
$data = array();
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

if (!empty($data)) {
    header('Content-Type: application/json');
    echo json_encode($data);
} else {
    header('Content-Type: application/json');
    echo json_encode(array('message' => 'No records found.'));
}

$con->close();
?>
