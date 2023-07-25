<?php
require_once 'db.php';

// Calculate the timestamp for 10000 minutes ago
//$timestamp = time() - (10000 * 60);
$timestamp = strtotime("-2 hours");
$query = "SELECT * FROM child WHERE UNIX_TIMESTAMP(date) >= $timestamp ORDER BY date DESC";
$result = $conn->query($query);


if ($result) {
    $children = []; // Initialize an empty array

    while ($row = $result->fetch_assoc()) { // Loop through the rows returned from the query
        $entry = [ 
            'child_name' => $row['string'],
            'parent_id' => $row['idP'],
            'date' => $row['date'],
            'number' => $row['number']
        ]; // Create a new entry in the array for each row
        $children[] = $entry; // Append the entry to the array
    }

    // Free the result set
    $result->free();

    // Close the database connection
    $conn->close();

    echo json_encode($children);
} else {
    echo "Failed to retrieve recently added children: " . $conn->error;
}
?>