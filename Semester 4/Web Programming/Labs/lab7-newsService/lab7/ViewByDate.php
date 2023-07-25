<?php
$con = new mysqli("localhost", "root", "", "news");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

if (isset($_GET['filter_by_date'])) {
    $filterByDate = $_GET['filter_by_date'];

    // prevent SQL injection
    $filterByDate = mysqli_real_escape_string($con, $filterByDate);

    $whereClause = '';

    if (!empty($filterByDate)) {
        $whereClause .= "date = '$filterByDate'";
    }

    $sql = "SELECT * FROM news";

    if (!empty($whereClause)) {
        $sql .= " WHERE $whereClause";
    }

    $result = $con->query($sql);
    $data = array();
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }

    if (!empty($data)) {
        echo json_encode($data);
    } else {
        echo json_encode(array('message' => 'No records found.'));
    }
}

$con->close();
?>
