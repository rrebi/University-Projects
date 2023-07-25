import { Button, Card, CardActions, CardContent, IconButton, TextField } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useNavigate, useParams } from "react-router-dom";

import { Publisher } from "../../models/Publisher";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import axios from "axios";
import { GlobalURL } from "../../constants";

export const PublisherAdd = () => {
	const navigate = useNavigate();

	const [publisher, setPublisher] = useState<Publisher>({
		publisher: "",
        year: 0,
		owner_name: "",
        format: "",
        country: "",
	});

	const addPublisher = async (event: { preventDefault: () => void }) => {
		event.preventDefault();
		try {
			await axios.post(`${GlobalURL}/publisher/`, publisher);
			navigate("/publisher");
		} catch (error) {
			console.log(error);
		}
	};

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<form onSubmit={addPublisher}>
						<TextField
							id="publisher"
							label="publisher"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event: React.ChangeEvent<HTMLInputElement>)=> setPublisher({ ...publisher, publisher: event.target.value })}
						/>
                        <TextField
							id="year"
							label="year"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event: React.ChangeEvent<HTMLInputElement>) => setPublisher({ ...publisher, year: Number(event.target.value) })}
						/>
						<TextField
							id="owner_name"
							label="owner_name"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event: React.ChangeEvent<HTMLInputElement>) => setPublisher({ ...publisher, owner_name: event.target.value })}
						/>
						 <TextField
							id="format"
							label="format"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event: React.ChangeEvent<HTMLInputElement>) => setPublisher({ ...publisher, format: event.target.value })}
						/>
						 <TextField
							id="country"
							label="country"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event: React.ChangeEvent<HTMLInputElement>) => setPublisher({ ...publisher, country: event.target.value })}
						/>

						<Button type="submit">Add Publisher</Button>
					</form>
				</CardContent>
				<CardActions></CardActions>
			</Card>
		</Container>
	);
};