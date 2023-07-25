<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json'); // Set the response content type to JSON

$con = new mysqli("localhost", "root", "", "news");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

if (isset($_GET['title'])) {
    $entryTitle = $_GET['title'];

    // prevent SQL injection
    $entryTitle = mysqli_real_escape_string($con, $entryTitle);

    // news by title
    $sql = "SELECT * FROM news WHERE Title = '$entryTitle'";

    // execute the query
    $result = $con->query($sql);

    if ($result->num_rows > 0) {
        $data = $result->fetch_assoc();
        echo json_encode($data);
    } else {
        echo json_encode(array('message' => 'No records found.'));
    }
}

$con->close();
?>
