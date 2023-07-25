<?php
require_once 'db.php';

if (isset($_GET['id'])) {
    $id = $_GET['id'];

    // Fetch the child from the database
    $stmt = $conn->prepare("SELECT * FROM child WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    $child = $result->fetch_assoc();

    if (!$child) {
        // Child with the given id doesn't exist
        echo "Child not found.";
        exit();
    }
    
    // Display confirmation message
    echo "Are you sure you want to delete child with ID: " . $child['id'] . "?";
    echo "<br>";
    echo "<a href=\"deleteC.php?id=" . $child['id'] . "&confirm=true\">Yes</a>";
    echo " | ";
    echo "<a href=\"getAllC.php\">No, go back</a>";

    if (isset($_GET['confirm']) && $_GET['confirm'] === 'true') {
        // Delete the parent from the database
        $stmt = $conn->prepare("DELETE FROM child WHERE id = ?");
        $stmt->bind_param("i", $id);
        $stmt->execute();

        // Redirect back to the parent list page
        header("Location: index.php");
        exit();
    }
}
?>
