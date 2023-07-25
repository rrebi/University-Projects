<?php
header('Access-Control-Allow-Origin: http://localhost:4200'); // Adjust the origin to match your Angular app URL
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json'); // Set the response content type to JSON


session_start();

$con = new mysqli("localhost", "root", "", "news");

if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

$errors = array();


if (true) {
try {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $data = json_decode(file_get_contents("php://input"),true);

        $producer = $data["Producer"];
        $title = $data["Title"];
        $text = $data["Text"];
        $date = $data["Date"];
        $category = $data["Category"];

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
            $stmt = $con->prepare("INSERT INTO news (title, text, producer, date, category) VALUES (?, ?, ?, ?, ?)");
            $stmt->bind_param("sssss", $title, $text, $producer, $date, $category);

            if ($stmt->execute()) {
                $response = [
                    'message' => 'The news' . htmlspecialchars($data["Title"]) . 'has been added',
                    'title' => htmlspecialchars($data["Title"]),
                    'text' => htmlspecialchars($data["Text"]),
                    'producer' => htmlspecialchars($data["Producer"]),
                    'date' => htmlspecialchars($data["Date"]),
                    'category' => htmlspecialchars($data["Category"])
                ];

                echo json_encode($response);
                
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
    //echo "Access denied. You do not have sufficient privileges.";
    // Or redirect to a different page
    //header("Location: restricted.html");
    //exit(); // Terminate the script

    echo json_encode("BAD");
    exit();
}

mysqli_close($con);
?>
