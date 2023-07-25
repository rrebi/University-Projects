<?php
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

        $_SESSION["role"] = $role;

        header("Location: addnews.html");
        exit();
    } else {
        echo "Invalid username or password.";
    }

    mysqli_close($con);
}
?>
