<?php

session_start();

$con = new mysqli("localhost", "root", "", "news");

if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

$errors = array();


if ($_SESSION["role"] == "user") {
try {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $producer = $_POST["Producer"];
        $title = $_POST["Title"];
        $text = $_POST["Text"];
        $date = $_POST["Date"];
        $category = $_POST["Category"];

        if (empty($producer)) {
            $errors[] = 'Producer is required.';
        }

        if (empty($title)) {
            $errors[] = 'Title is required.';
        }

        if (empty($text)) {
            $errors[] = 'Text is required.';
        }

        if (empty($date)) {
            $errors[] = 'Date is required.';
        }

        if (empty($category)) {
            $errors[] = 'Category is required.';
        }

        if (empty($errors)) {
            $stmt = $con->prepare("INSERT INTO news (producer, title, text, date, category) VALUES (?, ?, ?, ?, ?)");
            $stmt->bind_param("sssss", $producer, $title, $text, $date, $category);

            if ($stmt->execute()) {
                echo 'News added successfully.';
                echo "<br />";
                echo 'Producer: ', htmlspecialchars($_POST["Producer"]);
                echo "<br />";
                echo 'Title: ', htmlspecialchars($_POST["Title"]);
                echo "<br />";
                echo 'Text: ', htmlspecialchars($_POST["Text"]);
                echo "<br />";
                echo 'Date: ', htmlspecialchars($_POST["Date"]);
                echo "<br />";
                echo 'Category: ', htmlspecialchars($_POST["Category"]);
                echo "<br />";

                
                header("Location: ViewAll.html");
                exit(); // Terminate the script
                
            } else {
                printf("%d Row inserted.\n", mysqli_affected_rows($con));
            }
            

            $stmt->close();
        }
    }
} catch (Exception $e) {
    echo 'Caught exception: ', $e->getMessage(), "\n";
}
}else {
    // Restrict access for non-admin users
    echo "Access denied. You do not have sufficient privileges.";
    // Or redirect to a different page
    //header("Location: restricted.html");
    exit(); // Terminate the script
}

mysqli_close($con);
?>
