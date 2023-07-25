import {
	TableContainer,
	Paper,
	Table,
	TableHead,
	TableRow,
	TableCell,
	TableBody,
	CircularProgress,
	Container,
	IconButton,
	Tooltip,
} from "@mui/material";
import axios from "axios";
import { styled } from '@mui/material/styles';
import { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import { Publisher } from "../../models/Publisher";
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import AddIcon from "@mui/icons-material/Add";
import { GlobalURL } from "../../constants";


const StyledTableRow = styled(TableRow)`
  &:hover {
    background-color: #ecebed;
  }
`;

export const PublisherAll = () => {
	const [loading, setLoading] = useState(false);
	const [publisher, setPublisher] = useState<Publisher[]>([]);

	useEffect(() => {
		setLoading(true);
		axios.get(`${GlobalURL}/publisher/`)
		  .then(response => {
			setPublisher(response.data);
			setLoading(false);
		  })
		  .catch(error => {
			console.error(error);
			setLoading(false);
		  });
	  }, []);

	return (
		<Container>
			<h1>All publishers</h1>

			{loading && <CircularProgress />}
			{!loading && publisher.length === 0 && <p>No publishers found</p>}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher/add`}>
					<Tooltip title="Add a new publisher" arrow>
						<AddIcon color="primary" />
					</Tooltip>
				</IconButton>
			)}
			{!loading && publisher.length > 0 && (
				<TableContainer component={Paper}>
					<Table sx={{ minWidth: 650 }} aria-label="simple table">
						<TableHead>
							<TableRow>
								<TableCell>#</TableCell>
								<TableCell align="right">Publisher</TableCell>
								<TableCell align="right">Year</TableCell>
								<TableCell align="right">Owner Name</TableCell>
                                <TableCell align="right">Format</TableCell>
                                <TableCell align="right">Country</TableCell>
                            
								<TableCell align="center">Operations</TableCell>
							</TableRow>
						</TableHead>
						<TableBody>
							{publisher.map((publisher, index) => (
								<StyledTableRow key={publisher.id}>
									<TableCell component="th" scope="row">
										{index + 1}
									</TableCell>
									<TableCell component="th" scope="row">
										<Link to={`/publisher/${publisher.id}/details`} title="View publisher details">
											{publisher.publisher}
										</Link>
									</TableCell>
                                    <TableCell align="right">{publisher.year}</TableCell>
									
                                    <TableCell align="right">{publisher.owner_name}</TableCell>
									<TableCell align="right">{publisher.format}</TableCell>
									<TableCell align="right">{publisher.country}</TableCell>
                                    
									<TableCell align="right">

										<IconButton
											component={Link}
											sx={{ mr: 3 }}
											to={`/publisher/${publisher.id}/details`}>
											<Tooltip title="View publisher details" arrow>
												<ReadMoreIcon color="primary" />
											</Tooltip>
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher/${publisher.id}/edit`}>
											<Tooltip title="Edit publisher details" arrow>
												<EditIcon />
											</Tooltip>
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher/${publisher.id}/delete`}>
											<Tooltip title="Delete publisher" arrow>
												<DeleteForeverIcon sx={{ color: "red" }} />
											</Tooltip>
										</IconButton>
									</TableCell>
								</StyledTableRow>
							))}
						</TableBody>
					</Table>
				</TableContainer>
			)}
		</Container>
	);
};