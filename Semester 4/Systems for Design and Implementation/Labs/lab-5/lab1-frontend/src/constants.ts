
const PROD_BACKEND_API_URL = "";
const DEV_BACKEND_API_URL = "http://127.0.0.1:8000";

export const GlobalURL =
	process.env.NODE_ENV === "development" ? DEV_BACKEND_API_URL : PROD_BACKEND_API_URL;