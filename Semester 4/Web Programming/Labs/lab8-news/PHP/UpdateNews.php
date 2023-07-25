<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, OPTIONS, PUT');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json');


session_start();

$con = new mysqli("localhost", "root", "", "news");

if (!$con) {
    die('Could not connect: ' . mysqli_error());
}


if (true) {
    // Allow access to all functionality

try {
    if ($_SERVER["REQUEST_METHOD"] == "PUT") {
        $data = json_decode(file_get_contents("php://input"), true);
            
        $titleToUpdate = mysqli_real_escape_string($con, $data["Title"]);
        $title = mysqli_real_escape_string($con, $data["Title"]);
        $producer = mysqli_real_escape_string($con, $data["Producer"]);
        $text = mysqli_real_escape_string($con, $data["Text"]);
        $date = mysqli_real_escape_string($con, $data["Date"]);
        $category = mysqli_real_escape_string($con, $data["Category"]);

        // Check if the title exists in the database
        $checkQuery = "SELECT * FROM news WHERE title = '$titleToUpdate'";
        $result = $con->query($checkQuery);

        if ($result->num_rows > 0) {
            $sql = "UPDATE news SET title='$title', producer='$producer', text='$text', date='$date', category='$category' WHERE (title = '$titleToUpdate')";
            $con->query($sql);

            $response = [
                'message' => 'The news ' . htmlspecialchars($data["Title"]) . ' has been updated',
                'title' => htmlspecialchars($data["Title"]),
                'text' => htmlspecialchars($data["Text"]),
                'producer' => htmlspecialchars($data["Producer"]),
                'date' => htmlspecialchars($data["Date"]),
                'category' => htmlspecialchars($data["Category"])
            ];

            echo json_encode($response);
            
        } else {
            echo json_encode("LOL");
            //echo 'News with the given title does not exist in the database.';
        }

        mysqli_close($con);
    }
} catch (Exception $e) {
   // echo 'Caught exception: ', $e->getMessage(), "\n";
}
}else {
    // Restrict access for non-admin users
    //echo "Access denied. You do not have sufficient privileges.";
    echo json_encode("Access denied");
    exit(); 
}

?>
