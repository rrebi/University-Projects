<?php
session_start();

$con = new mysqli("localhost", "root", "", "news");

if (!$con) {
    die('Could not connect: ' . mysqli_error());
}


if ($_SESSION["role"] == "user") {
    // Allow access to all functionality

try {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $titleToUpdate = mysqli_real_escape_string($con, $_POST["Title"]);
        $title = mysqli_real_escape_string($con, $_POST["Title"]);
        $producer = mysqli_real_escape_string($con, $_POST["Producer"]);
        $text = mysqli_real_escape_string($con, $_POST["Text"]);
        $date = mysqli_real_escape_string($con, $_POST["Date"]);
        $category = mysqli_real_escape_string($con, $_POST["Category"]);

        // Check if the title exists in the database
        $checkQuery = "SELECT * FROM news WHERE title = '$titleToUpdate'";
        $result = $con->query($checkQuery);

        if ($result->num_rows > 0) {
            $sql = "UPDATE news SET title='$title', producer='$producer', text='$text', date='$date', category='$category' WHERE (title = '$titleToUpdate')";
            $con->query($sql);

            echo 'News updated successfully.';
            
            header("Location: ViewAll.html");
            exit(); // Terminate the script
        } else {
            echo 'News with the given title does not exist in the database.';
        }

        mysqli_close($con);
    }
} catch (Exception $e) {
    echo 'Caught exception: ', $e->getMessage(), "\n";
}
}else {
    // Restrict access for non-admin users
    echo "Access denied. You do not have sufficient privileges.";
  
    exit(); 
}

?>
