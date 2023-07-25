<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json'); // Set the response content type to JSON

session_start();

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST["username"];
    $password = $_POST["password"];

    $con = new mysqli("localhost", "root", "", "news");
    if (!$con) {
        die('Could not connect: ' . mysqli_error());
    }

    $sql = "SELECT * FROM user WHERE username = '$username' AND password = '$password'";
    $result = $con->query($sql);

    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();

        $role = $row["role"];

        $response = $role;

        echo json_encode($response);

        // Store the role in the session
        $_SESSION["role"] = $role;

        exit();
    } else {
        //echo "Invalid username or password.";
    }

    mysqli_close($con);
}
?>
