<?php
require_once 'db.php';

if (isset($_GET['id'])) {
    $id = $_GET['id'];

    // Fetch the parent from the database
    $stmt = $conn->prepare("SELECT * FROM parent WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    $parent = $result->fetch_assoc();

    if (!$parent) {
        // Parent with the given id doesn't exist
        echo "Parent not found.";
        exit();
    }
    
    // Display confirmation message
    echo "Are you sure you want to delete parent with ID: " . $parent['id'] . "?";
    echo "<br>";
    echo "<a href=\"deleteP.php?id=" . $parent['id'] . "&confirm=true\">Yes</a>";
    echo " | ";
    echo "<a href=\"getAllP.php\">No, go back</a>";

    if (isset($_GET['confirm']) && $_GET['confirm'] === 'true') {
        // Delete the parent from the database
        $stmt = $conn->prepare("DELETE FROM parent WHERE id = ?");
        $stmt->bind_param("i", $id);
        $stmt->execute();

        // Redirect back to the parent list page
        header("Location: index.php");
        exit();
    }
}
?>
