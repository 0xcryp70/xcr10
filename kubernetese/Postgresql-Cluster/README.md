```helm repo add bitnami https://charts.bitnami.com/bitnami <br>
helm install my-postgres-ha bitnami/postgresql-ha -f values.yaml -n postgresql <br>
export PASSWORD=$(kubectl get secret --namespace "default" my-postgres-ha-postgresql-ha-postgresql -o jsonpath="{.data.password}" | base64 -d) <br>
```
<br>
<br>
<br>
<br>
Update: <br>
```
export PASSWORD=$(kubectl get secret --namespace "default" my-postgres-ha-postgresql-ha-postgresql -o jsonpath="{.data.password}" | base64 -d) <br>
export REPMGR_PASSWORD=$(kubectl get secret --namespace "default" my-postgres-ha-postgresql-ha-postgresql -o jsonpath="{.data.repmgr-password}" | base64 -d ) <br>
export ADMIN_PASSWORD=$(kubectl get secret --namespace "default" my-postgres-ha-postgresql-ha-pgpool -o jsonpath="{.data.admin-password}" | base64 -d) <br>
helm upgrade --install my-postgres-ha bitnami/postgresql-ha --set postgresql.password=$PASSWORD  --set postgresql.repmgrPassword=$REPMGR_PASSWORD --set pgpool.adminPassword=$ADMIN_PASSWORD -f values.yaml -n postgresql <br> 
```