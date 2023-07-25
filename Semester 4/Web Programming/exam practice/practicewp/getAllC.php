<?php
require_once 'db.php';

// Initialize variables for ordering
$order = isset($_GET['order']) ? $_GET['order'] : 'asc';
$orderBy = ($order === 'asc') ? 'ASC' : 'DESC';

// Fetch all children from the database with ordering
//$stmt = $conn->query("SELECT * FROM child ORDER BY number $orderBy");
$stmt = $conn->query("SELECT *, (0.2 * idP + 0.6 * number) AS calculated_order FROM child ORDER BY calculated_order $orderBy");

$children = $stmt->fetch_all(MYSQLI_ASSOC); 
?>


<!DOCTYPE html>
<html>
<head>
  <title>All Children</title>
  <style>
    table {
      border-collapse: collapse; 
      width: 100%;
    }
    th, td {
      border: 1px solid black;
      padding: 8px;
      text-align: center;
    }
    .red-bg {
      background-color: blue;
    }
  </style>
</head>
<body>
  <h1>All Children</h1>
  <form method="GET" action="getAllC.php">
    <input type="hidden" name="order" value="<?php echo ($order === 'asc') ? 'desc' : 'asc'; ?>">
    <input type="submit" value="Order by Number <?php echo ($order === 'asc') ? 'Desc' : 'Asc'; ?>">
  </form>
  <table>
    <tr>
      <th>ID</th>
      <th>idP</th>
      <th>String</th>
      <th>Date</th>
      <th>Number</th>
      <th>Calculated Order</th>
      <th>Actions</th>
    </tr>
    <?php foreach ($children as $child) { ?>
    <tr <?php if($child['number']>8) echo 'class="red-bg"';?>>
      <td><?php echo $child['id']; ?></td> 
      <td><?php echo $child['idP']; ?></td> 
      <td><?php echo $child['string']; ?></td>
      <td><?php echo $child['date']; ?></td>      
      <td><?php echo $child['number']; ?></td>
      <td><?php echo $child['calculated_order']; ?></td>
      <td>
        <a href="updateC.php?id=<?php echo $child['id']; ?>">Update</a> |
        <a href="deleteC.php?id=<?php echo $child['id']; ?>">Delete</a>
      </td>
    </tr>
    <?php } ?>
  </table>
</body>
</html>


<!-- <div>
    //for paginated and ordered you might need this
  <//?php if ($page > 1) { ?>
    <a href="getAllC.php?order=</?php echo $order; ?>&page=</?php echo $prevPage; ?>">Previous Page</a>
  <//?php } ?>
  
  <//?php if ($page < $totalPages) { ?>
    <a href="getAllC.php?order=</?php echo $order; ?>&page=</?php echo $nextPage; ?>">Next Page</a>
  <//?php } ?>
</div> -->
