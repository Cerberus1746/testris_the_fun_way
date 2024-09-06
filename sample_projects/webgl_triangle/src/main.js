import { asyncRun } from "./py-worker.js";

const script = `
from clockwork_reverie_py.math import Vector3Int
Vector3Int(55, 12, 32).magnitude()
`;

async function main() {
  try {
    const { results, error } = await asyncRun(script);
    if (results) {
      console.log("pyodideWorker return results: ", results);
    } else if (error) {
      console.log("pyodideWorker error: ", error);
    }
  } catch (e) {
    console.log(
      `Error in pyodideWorker at ${e.filename}, Line: ${e.lineno}, ${e.message}`,
    );
  }
}

main();
