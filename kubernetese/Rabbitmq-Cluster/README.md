namespace : default

Run this command inside one of the RabbitMQ cluster pods:

```
rabbitmqctl set_policy ha-fed     ".*" '{"federation-upstream-set":"all", "ha-sync-mode":"automatic", "ha-mode":"nodes", "ha-params":["rabbit@rabbitmq-app-0.rabbitmq-srv.rabbits.svc.cluster.local","rabbit@rabbitmq-app-1.rabbitmq-srv.rabbits.svc.cluster.local","rabbit@rabbitmq-app-2.rabbitmq-srv.rabbits.svc.cluster.local"]}' --priority 1 --apply-to queues
```
