<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json'); // Set the response content type to JSON

session_start();

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    $_SESSION["role"] = "visitor";

    echo json_encode("Success");
    exit();
}
?>
