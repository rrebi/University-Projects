<?php
require_once 'db.php';
session_start();

// Check if the shopping basket exists in the session
if (isset($_SESSION['shopping_basket']) && !empty($_SESSION['shopping_basket'])) {
    $shoppingBasket = $_SESSION['shopping_basket'];
} else {
    $shoppingBasket = [];
}

// Handle increasing or decreasing the number of children
// Handle increasing or decreasing the number of children
if (isset($_POST['add_child'])) {
    $childID = $_POST['child_id'];

    // Increase the number of children
    if (!isset($_SESSION['child_counts'][$childID])) {
        $_SESSION['child_counts'][$childID] = 1;
    } else {
        $_SESSION['child_counts'][$childID]++;
    }
} elseif (isset($_POST['remove_child'])) {
    $childID = $_POST['child_id'];

    // Decrease the number of children
    if (isset($_SESSION['child_counts'][$childID])) {
        $_SESSION['child_counts'][$childID]--;
        if ($_SESSION['child_counts'][$childID] === 0) {
            unset($_SESSION['child_counts'][$childID]);
            unset($shoppingBasket[$childID]);
        }
    }
}


// Handle finishing the shopping
if (isset($_POST['finish_shopping'])) {
    // Check if there are children in the shopping basket
    if (!empty($shoppingBasket)) {
        // Retrieve the parent ID from the session
        $parentID = $_SESSION['parent_id'];

        // Get the current date
        $date = date("Y-m-d H:i:s");

        // Prepare and execute the SQL query to insert data into the child table
        $stmt = $conn->prepare("INSERT INTO child (idP, string, date, number) VALUES (?, ?, ?, ?)");

        // Insert each child from the shopping basket
        foreach ($shoppingBasket as $childID => $childString) {
            $childCount = isset($_SESSION['child_counts'][$childID]);// ? $_SESSION['child_counts'][$childID] : 0;

            $stmt->bind_param("sssi", $parentID, $childString, $date, $childCount);
            $stmt->execute();
        }

        // Check if any rows were affected
        if ($stmt->affected_rows > 0) {
            echo "Children added successfully!";
        } else {
            echo "Failed to add children.";
        }

        // Close the statement
        $stmt->close();

        // Clear the shopping basket and child counts
        unset($_SESSION['shopping_basket']);
        unset($_SESSION['child_counts']);
        header("Location: viewShoppingBasket.php");
    }
}

// Handle canceling the order
if (isset($_POST['cancel_order'])) {
    unset($_SESSION['shopping_basket']);
    unset($_SESSION['child_counts']);
    header("Location: viewShoppingBasket.php");
    exit();
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Shopping Basket</title>
</head>
<body>
    <h1>Shopping Basket</h1>
    <?php if (!empty($shoppingBasket)) : ?>
    <ul>
        <?php foreach ($shoppingBasket as $childID => $childString) : ?>
            <?php if (isset($_SESSION['child_counts'][$childID]) && $_SESSION['child_counts'][$childID] > 0) : ?>
                <li>
                    <?php echo $childString; ?>
                    <form action="" method="post" style="display:inline-block;">
                        <input type="hidden" name="child_id" value="<?php echo $childID; ?>">
                        <input type="submit" name="add_child" value="+">
                        <span><?php echo $_SESSION['child_counts'][$childID]; ?></span>
                        <input type="submit" name="remove_child" value="-">
                    </form>
                </li>
            <?php endif; ?>
        <?php endforeach; ?>
    </ul>
    
    <form action="" method="post">
        <input type="submit" name="finish_shopping" value="Finish Shopping">
        <input type="submit" name="cancel_order" value="Cancel Order">
    </form>
    
<?php else : ?>
    <p>Your shopping basket is empty.</p>
<?php endif; ?>


    <a href="shoppingBasket.php">Add Child</a>
</body>
</html>
